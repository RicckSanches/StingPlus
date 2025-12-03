CFLAGS = -Wall -Werror -Wextra -std=c11
CC = gcc

all: clean string

string:
	$(CC) $(CFLAGS) s21_string.c main.c -o main

clang:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

rebuild:
	make clean
	make all

clean:
	rm -rf string 

test:

