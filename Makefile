# OS and Architecture detection
ifeq ($(OS), Windows_NT)
	OS = Windows
	ifeq ($(PROCESSOR_ARCHITECTURE), AMD64)
		ARCH = x86_64
	else ifeq ($(PROCESSOR_ARCHITECTURE), IA64)
		ARCH = x86_64
	else ifeq ($(PROCESSOR_ARCHITECTURE), EM64T)
		ARCH = x86_64
	else ifeq ($(PROCESSOR_ARCHITECTURE), ARM64)
		ARCH = AArch64
	else ifeq ($(PROCESSOR_ARCHITECTURE), X86)
		ARCH = i386
	endif
else
    OS = $(shell uname -s)
	ARCH = $(shell uname -m)
endif

SDL = SDL2-2.0.14
TTF = SDL2_ttf-2.0.15
IMG = SDL2_image-2.0.5

compiler = $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation compiler)
ifeq ($(compiler),)
	compiler = gcc
endif

debugger = $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation debugger)
ifeq ($(debugger),)
	debugger = gdb
endif

exec = $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation exec)
ifeq ($(exec),)
	exec = main
endif

user_sources = $(addsuffix .o, $(basename $(wildcard src/game/*.c)))
test_sources = $(addsuffix .o, $(basename $(wildcard tests/*.c)))
sources = $(wildcard src/engine/*.c) $(wildcard src/engine/vendor/inih/*.c)
objects = $(sources:.c=.o)

cflags = -pedantic-errors -Wall -Wextra $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation cflags)
ifeq ($(OS), Darwin)
	cflags += -I/usr/local/Cellar
endif
inih_flags = -DINI_USE_STACK=0 -DINI_ALLOW_REALLOC=1
flags = $(cflags) $(inih_flags)
lib_flags = -lSDL2 -lSDL2_ttf -lSDL2_image
ifneq ($(OS), Darwin)
	lib_flags += -lX11
endif

all: $(user_sources)
all: objects += $(user_sources)
all: $(exec) ### Build the project

debug: flags += -g -DDEBUG
debug: clean
debug: all ### Generate debug symbols for project and enter debugger
	@echo $(OS) $(ARCH)
	@$(debugger) $(exec)

release: flags += -O3 -DRELEASE
release: all ### Append release flags and build the project

test: flags += -DTEST
test: clean
test: $(test_sources)
test: objects += $(test_sources)
test: $(exec) ### Run unit tests (CUnit)
	./$(exec)

$(exec): $(objects)
	@$(compiler) $(objects) $(flags) $(lib_flags) -o $(exec) 

%.o: %.c
	@$(compiler) -c $(flags) $< -o $@

clean: ### Remove all generated files
	-@rm $(shell find src/ -name *.o)
	-@rm $(exec)

documentation: ### Generates documentation for sources (Doxygen)
	-@rm -rf docs/*
	@doxygen Doxyfile

libtool = libtoolize
ifeq ($(OS), Darwin)
	libtool = glibtoolize
endif
get-deps:
	@curl -L https://www.libsdl.org/release/$(SDL).tar.gz | tar xz
	@cd $(SDL) && ./configure && make && sudo make install
	@rm -rf $(SDL)

	@curl -L https://www.libsdl.org/projects/SDL_ttf/release/$(TTF).tar.gz | tar xz
	@cd $(TTF) && ./configure && make && sudo make install
	@rm -rf $(TTF)
	
	@curl -L https://www.libsdl.org/projects/SDL_image/release/$(IMG).tar.gz | tar xz
	@cd $(IMG) && ./configure && make && sudo make install
	@rm -rf $(IMG)

	# Thanks to http://blog.cleverelephant.ca/2014/12/building-cunit-from-source.html
	@git clone https://github.com/jacklicn/CUnit
	@cd CUnit && $(libtool) -f -c -i && aclocal && autoheader && autoconf && automake --gnu --add-missing && ./configure && make && sudo make install
	@rm -rf CUnit
	
help: ### Show this list 
	@fgrep -h "###" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/###//'
