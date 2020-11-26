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

# Generate docs from targets
help: ### Show this list 
	@fgrep -h "###" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/###//'