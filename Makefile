compiler = gcc
debugger = lldb

exec = main
sources = $(shell find src/ -type f -name '*.c')
objects = $(sources:.c=.o)
flags = -g -std=c18 -pedantic-errors -Wall -Wextra -I/usr/local/include/SDL2 -D_THREAD_SAFE
libs = -L/usr/local/lib -lSDL2 -lSDL2_ttf -lSDL2_image

$(exec): $(objects)
	@$(compiler) $(objects) $(flags) $(libs) -o $(exec) 

%.o: %.c include/%.h
	@$(compiler) -c $(flags) $< -o $@

clean:
	@rm $(exec)
	@rm $(objects)

debug:
	@make
	@dsymutil $(exec)
	@$(debugger) $(exec)