CFLAGS = -g -Wall
CC = gcc

objects =  parse.o myshell.o

test: $(objects)
	$(CC) $(CFLAGS) -o shell $(objects)
parse: parse.o
	$(CC) $(CFLAGS) -o parse parse.o
myshell: myshell.o
	$(CC) $(CFLAGS) -o myshell myshell.o

parse.o: parse.c parse.h 
myshell.o: myshell.c parse.h
.PHONY : clean
clean: 
	rm shell $(objects)
