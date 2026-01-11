CFLAGS = -Wall -Werror -Wextra -std=c11
CC = gcc
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

# ===== Проверка ОС для линковки Check =====
OS := $(shell uname)

ifeq ($(OS),Linux)
  CHECK_LIBS = -lcheck -lsubunit -lm -lpthread
else
  CHECK_LIBS = -lcheck
endif


all: clean string

string: Makefile s21_strlen.c s21_string.c s21_string.h s21_sprintf.c
	$(CC) $(CFLAGS) s21_strlen.c string.c string_c.h s21_error.h s21_sprintf.c -o string.o




clang:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

rebuild:
	make clean
	make all

clean:
	rm -rf string 

test:
	$(CC) $(CFLAGS) s21_string_tests.c -o test.o


