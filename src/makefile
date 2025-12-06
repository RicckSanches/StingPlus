CFLAGS = -Wall -Werror -Wextra -std=c11
CC = gcc

all: clean string

string: Makefile s21_strlen.c string.c string_c.h tests.c
	$(CC) $(CFLAGS) s21_strlen.c string.c string_c.h s21_error.h tests.c -o test


clang:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

rebuild:
	make clean
	make all

clean:
	rm -rf string 

test:


