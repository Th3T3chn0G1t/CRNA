compiler = gcc
debugger = lldb

exec = main
sources = $(shell find src/ -type f -name '*.c')
objects = $(sources:.c=.o)
inih_flags = -DINI_USE_STACK=0 -DINI_ALLOW_REALLOC=1
flags = -g -std=c18 -pedantic-errors -Wall -Wextra -I/usr/local/include/SDL2 -D_THREAD_SAFE
libs = -L/usr/local/lib -lSDL2 -lSDL2_ttf -lSDL2_image

$(exec): $(objects)
	@$(compiler) $(objects) $(inih_flags) $(flags) $(libs) -o $(exec) 

%.o: %.c include/%.h
	@$(compiler) -c $(inih_flags) $(flags) $< -o $@

clean:
	@rm $(objects)
	@rm logs/*
	@rm $(exec)
	@rm -rf $(exec).dSYM

debug:
	@make
	@dsymutil $(exec)
	@$(debugger) $(exec)
