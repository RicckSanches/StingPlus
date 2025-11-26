CFLAGS = -Wall -Werror -Wextra -std=c11
CC = gcc

all: clean string

string: Makefile string.h main.c
	$(CC) $(CFLAGS) main.c -o main


clang:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

rebuild:
	make clean
	make all

clean:
	rm -rf string 

test:

