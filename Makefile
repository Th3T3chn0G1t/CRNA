SDL_VERSION = SDL2-2.0.12
TTF_VERSION = SDL2_ttf-2.0.15
IMG_VERSION = SDL2_image-2.0.5

compiler = $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation compiler)
debugger = $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation debugger)

exec 	  = $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation exec)

sources = $(wildcard src/engine/*.c) $(wildcard src/engine/vendor/inih/*.c) $(wildcard src/game/*.c)
objects = $(sources:.c=.o)

cflags     = -pedantic-errors -Wall -Wextra -I/usr/local/Cellar $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation cflags)
inih_flags = -DINI_USE_STACK=0 -DINI_ALLOW_REALLOC=1

flags     = $(cflags) $(inih_flags)
lib_flags = -lX11 -lSDL2 -lSDL2_ttf -lSDL2_image

build: $(exec) ### Build the project

debug: flags += -g -DDEBUG
debug: $(exec) ### Generate debug symbols for program and enter debugger
	@$(debugger) $(exec)

release: flags += -O2 -DRELEASE
release: $(exec) ### Append release flags and build the program

#test: flags += -DTEST
#test: $(exec) ### Run unit tests (CUnit) TODO Fix

$(exec): $(objects)
	@$(compiler) $(objects) $(flags) $(lib_flags) -o $(exec) 

%.o: %.c
	@$(compiler) -c $(flags) $< -o $@

clean: ### Remove all generated files
	-@rm $(objects)
	-@rm $(exec)

documentation: ### Generates documentation for sources (Doxygen)
	-@rm -rf docs/*
	@doxygen Doxyfile

get-deps:
	curl -L https://www.libsdl.org/release/$(SDL_VERSION).tar.gz | tar xz
	cd $(SDL_VERSION) && ./configure && make && sudo make install
	rm -rf $(SDL_VERSION)

	curl -L https://www.libsdl.org/projects/SDL_ttf/release/$(TTF_VERSION).tar.gz | tar xz
	cd $(TTF_VERSION) && ./configure && make && sudo make install
	rm -rf $(TTF_VERSION)
	
	curl -L https://www.libsdl.org/projects/SDL_image/release/$(IMG_VERSION).tar.gz | tar xz
	cd $(IMG_VERSION) && ./configure && make && sudo make install
	rm -rf $(IMG_VERSION)

help: ### Show this list 
	@fgrep -h "###" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/###//'
