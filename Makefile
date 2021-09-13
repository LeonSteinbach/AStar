CC = gcc
CFLAGS = --std=c11 -pedantic -Wall -Wuninitialized

all: compile test

compile: main

inc.o: inc.c inc.h
	$(CC) $(CFLAGS) inc.c -c

abc: inc.o inc.h main.c
	$(CC) $(CFLAGS) inc.o main.c -o execute_me

main: main.c
	$(CC) $(CFLAGS) main.c -o astar -lm

test:
	./astar
