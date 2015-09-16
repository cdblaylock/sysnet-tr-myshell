CFLAGS = -g -Wall
CC = gcc

objects =  parse.o myshell.o slow.o

test: $(objects)
	$(CC) $(CFLAGS) -o myshell $(objects)
parse: parse.o
	$(CC) $(CFLAGS) -o parse parse.o
myshell: myshell.o
	$(CC) $(CFLAGS) -o myshell myshell.o
slow: slow.o
	$(CC) $(CFLAGS) -o myshell myshell.o

slow.o: slow.c
parse.o: parse.c parse.h 
myshell.o: myshell.c parse.h
.PHONY : clean
clean: 
	rm myshell $(objects)
