# Makefile for building s21_sprintf static library and tests

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2
GCOV_FLAGS = --coverage
CHECK_LIBS = -lcheck -lsubunit -pthread -lrt -lm

SRCS = s21_sprintf.c s21_string.c utils.c
OBJS = $(SRCS:.c=.o)
GCOV_OBJS = $(SRCS:.c=.gc.o)

AR = ar
ARFLAGS = rcs

LIB = s21_string.a
LIB_GCOV = s21_string_gcov.a
TEST_DIR = tests
TEST_SRC = $(TEST_DIR)/s21_sprintf_test.c 
TEST_SRC_STRING = $(TEST_DIR)/s21_string_test.c
TEST_SRC_UTILS = $(TEST_DIR)/utils_tests.c
TEST_BIN = s21_sprintf_test
TEST_BIN_STRING = s21_string_test
TEST_BIN_UTILS = utils_tests
GCOV_DIR = report

.PHONY: all clean test gcov_report

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJS)

test: $(LIB)
	$(CC) $(CFLAGS) -I. $(TEST_SRC) -L. $(LIB) $(CHECK_LIBS) -o $(TEST_BIN)
	./$(TEST_BIN)
	$(CC) $(CFLAGS) -I. $(TEST_SRC_STRING) -L. $(LIB) $(CHECK_LIBS) -o $(TEST_BIN_STRING)
	./$(TEST_BIN_STRING)
	$(CC) $(CFLAGS) -I. $(TEST_SRC_UTILS) -L. $(LIB) $(CHECK_LIBS) -o $(TEST_BIN_UTILS)
	./$(TEST_BIN_UTILS)

%.gc.o: %.c
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -I. -c $< -o $@

$(LIB_GCOV): $(GCOV_OBJS)
	$(AR) $(ARFLAGS) $(LIB_GCOV) $(GCOV_OBJS)

gcov_report: clean $(LIB_GCOV)
	# Build and run sprintf tests
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -I. $(TEST_SRC) -L. $(LIB_GCOV) $(CHECK_LIBS) -o $(TEST_BIN)
	-./$(TEST_BIN) || true
	
	# Build and run string tests
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -I. $(TEST_SRC_STRING) -L. $(LIB_GCOV) $(CHECK_LIBS) -o $(TEST_BIN_STRING)
	-./$(TEST_BIN_STRING) || true
	
	# Generate coverage report
	mkdir -p $(GCOV_DIR)
	lcov -t "s21_tests" -o $(GCOV_DIR)/report.info -c -d . --ignore-errors source
	genhtml -o $(GCOV_DIR) $(GCOV_DIR)/report.info
	@echo "Report generated in $(GCOV_DIR)/index.html"
	@echo "Open $(GCOV_DIR)/index.html in your browser to view the report"

clean:
	rm -rf $(OBJS) $(GCOV_OBJS) $(LIB) $(LIB_GCOV) $(TEST_BIN) $(TEST_BIN_STRING) $(TEST_BIN_UTILS) *.gcda *.gcno *.gcov *.log *.tap $(GCOV_DIR)