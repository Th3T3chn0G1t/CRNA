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
	ifeq ($(OS),)
	    OS = $(shell uname -s)
		ARCH = $(shell uname -m)
	endif
endif

ifeq ($(OS), Darwin)
U_SHELL = $(shell dscl . -read ~/ UserShell | sed 's/UserShell: //')
else ifeq ($(OS), Windows)
U_SHELL = C:/windows/cmd.exe
else
U_SHELL = $(shell finger $(USER) | grep -oP 'Shell: \K.*')
endif

SDL = SDL2-2.0.14
TTF = SDL2_ttf-2.0.15
IMG = SDL2_image-2.0.5

compiler = $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation compiler)
ifndef $(compiler)
	compiler = gcc
endif

exec = $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation exec)
ifndef $(exec)
	exec = main
endif

test_objects = $(addsuffix .o, $(basename $(wildcard src/tests/*.c)))
sources = $(wildcard src/engine/*.c) $(wildcard src/engine/vendor/inih/*.c)
objects = $(sources:.c=.o)

cflags = -Wpedantic -Wall -Wextra $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation cflags)
ifeq ($(OS), Darwin)
	cflags += -I/usr/local/Cellar
else ifeq ($(OS), Windows)
	cflags += -D_WIN32
endif
inih_flags = -DINI_USE_STACK=0 -DINI_ALLOW_REALLOC=1
flags = $(cflags) $(inih_flags)
linker_flags = -lSDL2 -lSDL2_ttf -lSDL2_image 
ifneq ($(OS), Darwin)
	linker_flags += -lX11
endif
prefix = /usr
ifeq ($(OS), Darwin)
	prefix = /usr/local
endif
dynamic_lib_suffix = so
ifeq ($(OS), Darwin)
	dynamic_lib_suffix = dylib
else ifeq ($(OS), Windows)
	dynamic_lib_suffix = dll
else 
	shared = 1
endif
static_lib_suffix = a
ifeq ($(OS), Windows)
	static_lib_suffix = lib
endif
# Libs TODO
# OS        Static       Done?    Dynamic     Done?
# Windows   .lib           Y      .dll          N // Long term maybe - .def files?
# *nix      .a             Y      .so           Y
# +Darwin                         .dylib        Y

ifeq ($(static), 1)
library: exec = libcrna.$(static_lib_suffix)
library: static
else
library: exec = libcrna.$(dynamic_lib_suffix)
library: dynamic
endif

ifeq ($(shared), 1)
dynamic: flags += -fPIC
dynamic: linker_flags += -shared
dynamic: dynamic_lib_suffix = so
#else ifeq ($(OS), Windows)
#ifneq ($(findstring mingw, compiler),)
#dynamic: linker_flags += -Wl,--out-implib,libcrna_dll.$(static_lib_suffix)
#else ifneq ($(findstring cygwin, compiler),)
#dynamic: linker_flags += -shared
#endif
else
dynamic: linker_flags += -dynamiclib
endif
dynamic: exec = libcrna.$(dynamic_lib_suffix)
dynamic: $(exec)

static: $(objects)
	ar rcs libcrna.$(static_lib_suffix) $(objects)

install: library
	-sudo cp $(exec) $(prefix)/lib/$(exec) && mkdir $(prefix)/include/crna && cp src/engine/include/*.h $(prefix)/include/crna/

debug: flags += -g -DDEBUG
debug: clean
debug: dynamic ### Generate debug symbols for project

release: flags += -O3 -DRELEASE
release: dynamic ### Append release flags and build the project

#test: $(test_objects)
#test: objects += $(test_objects)
#test: flags += -DTEST
#test: $(exec) ### Run unit tests (CUnit): FIX THEM NOW
#	./$(exec)

$(exec): $(objects)
	$(compiler) $(objects) $(flags) $(linker_flags) -o $(exec) 

%.o: %.c
	$(compiler) -c $(flags) $< -o $@

clean: ### Remove all generated files
	-@rm $(shell find src/ -name *.o)
	-@rm $(exec)

documentation: ### Generates documentation for sources (Doxygen)
	-@rm -rf docs/*
	doxygen Doxyfile

libtool = libtoolize
ifeq ($(OS), Darwin)
	libtool = glibtoolize
endif
get-deps:
	curl -L https://www.libsdl.org/release/$(SDL).tar.gz | tar xz
	cd $(SDL) && ./configure && make && sudo make install
	rm -rf $(SDL)

	curl -L https://www.libsdl.org/projects/SDL_ttf/release/$(TTF).tar.gz | tar xz
	cd $(TTF) && ./configure && make && sudo make install
	rm -rf $(TTF)
	
	curl -L https://www.libsdl.org/projects/SDL_image/release/$(IMG).tar.gz | tar xz
	cd $(IMG) && ./configure && make && sudo make install
	rm -rf $(IMG)

	# Thanks to http://blog.cleverelephant.ca/2014/12/building-cunit-from-source.html
	git clone https://github.com/jacklicn/CUnit
	cd CUnit && $(libtool) -f -c -i && aclocal && autoheader && autoconf && automake --gnu --add-missing && ./configure && make && sudo make install
	rm -rf CUnit
	
help: ### Show this list 
	@fgrep -h "###" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/###//'
