CFLAGS = -Wall -Werror -Wextra -std=c11
CC = gcc

all: clean string

string: Makefile string.h string.c
	$(CC) $(CFLAGS) string.c -o string


clang:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

rebuild:
	make clean
	make all

clean:
	rm -rf string

test:

