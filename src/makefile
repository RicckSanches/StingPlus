# Makefile for building s21_sprintf static library and tests

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2
CHECK_LIBS = -lcheck -lsubunit -pthread -lrt -lm

SRCS = s21_sprintf.c
OBJS = $(SRCS:.c=.o)

AR = ar
ARFLAGS = rcs

LIB = s21_string.a
TEST_DIR = tests
TEST_SRC = $(TEST_DIR)/s21_sprintf_test.c
TEST_BIN = s21_sprintf_test

.PHONY: all clean test s21_string.a gcov_report

all: $(LIB) test

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJS)

test: $(LIB)
	$(CC) $(CFLAGS) -I. $(TEST_SRC) -L. -l:$(LIB) $(CHECK_LIBS) -o $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(OBJS) $(LIB) $(TEST_BIN) *.gcda *.gcno *.gcov
