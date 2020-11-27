compiler = $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation compiler)
debugger = $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation debugger)

exec = $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation exec)

sources = $(shell find src/ -type f -iname "*.c")
objects = $(sources:.c=.o)
test_sources = $(shell find src/ -type f -iname "*.c" -path "./src/game" -prune) $(shell find tests/ -type f -iname "*.c")
test_objects = $(test_sources:.c=.o)

cflags = -std=c18 -pedantic-errors -Wall -Wextra -I/usr/local/Cellar -I/usr/local/include/SDL2 -D_THREAD_SAFE
inih_flags = -DINI_USE_STACK=0 -DINI_ALLOW_REALLOC=1
user_flags = $(shell scripts/keyFromSection.sh .crna/build_settings.ini compilation cflags)
buildtime_flags =
lib_flags = -L/usr/local/lib -lSDL2 -lSDL2_ttf -lSDL2_image

logfile = $(shell scripts/keyFromSection.sh .crna/build_settings.ini logging logfile)
tests_logfile = $(shell scripts/keyFromSection.sh .crna/build_settings.ini logging tests_logfile)

SDL_VERSION = SDL2-2.0.12
TTF_VERSION = SDL2_ttf-2.0.15
IMG_VERSION = SDL2_image-2.0.5

CUNIT_VERSION = 2.1-2

build: ### Build the project
	@time make $(exec) -j 2>&1 | tee $(logfile) 
	@echo "Complete!"

$(exec): $(objects)
	@$(compiler) $(objects) $(buildtime_flags) $(inih_flags) $(cflags) $(user_flags) $(lib_flags) -o $(exec) 

%.o: %.c include/%.h
	@$(compiler) -c $(buildtime_flags) $(inih_flags) $(cflags) $(user_flags) $< -o $@

clean: ### Remove all generated files + logfiles
	-@rm $(objects)
	-@rm $(test_objects)
	-@rm logs/*
	-@rm $(exec)
	-@rm -rf $(exec).dSYM

rebuild: ### Cleans and rebuilds the project
	@make clean
	@make	

run: ### Build and execute the program
	@make
	@./$(exec)

debug: buildtime_flags = -g -DDEBUG
debug: ### Generate debug symbols for program and enter debugger
	@make
	@dsymutil $(exec)
	@$(debugger) $(exec)


release: buildtime_flags = -O3 -DRELEASE
release: ### Append release flags and build the program
	@make
test_objects: $(test_objects)
	@exit
test: ### Run unit tests (CUnit)
	@make test_objects
	@$(compiler) $(test_objects) $(buildtime_flags) $(inih_flags) $(cflags) $(user_flags) $(lib_flags) -lCUnit -o $(exec) 2>&1 | tee $(logfile)
	@time ./$(exec) -j 2>&1 | tee $(tests_logfile) 
	@echo "Complete!"

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

	curl -L http://downloads.sourceforge.net/project/cunit/CUnit/$(CUNIT_VERSION)/CUnit-$(CUNIT_VERSION)-src.tar.bz2 | tar xvj
	cd CUnit-$(CUNIT_VERSION) && libtoolize -f -c -i \
		&& aclocal \
		&& autoconf \
		&& automake --gnu --add-missing \
		&& ./configure --prefix=/usr/local \
		&& make \
		&& sudo make install
	rm -rf CUnit-$(CUNIT_VERSION)

	git clone https://github.com/doxygen/doxygen.git
	mkdir doxygen/build
	cd doxygen/build && cmake -G "Unix Makefiles" .. && make && sudo make install
	
# Generate docs from targets
help: ### Show this list 
	@fgrep -h "###" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/###//'