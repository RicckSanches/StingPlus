CFLAGS = -Wall -Werror -Wextra -std=c11
CC = gcc
LDFLAGS = -lcheck -lm -lpthread -lsubunit
LCOVFLAGS = -O0 --coverage

all: clean string

string:
	$(CC) $(CFLAGS) s21_string.c main.c -o main

test:
	gcc tests.c s21_string.c $(LCOVFLAGS) $(LDFLAGS) -o test_program
	./test_program
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_html
	@echo "Coverage report generated: coverage_html/index.html"

clang:
	clang-format -n *.c *.h
	clang-format -i *.c *.h

rebuild:
	make clean
	make all

clean:
	rm -rf string 
	rm test_program* 
	rm coverage.info
	rm -rf coverage_html/