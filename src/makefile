CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
LIBS = -lcheck

all: test_string test_sprintf

test_string:
	$(CC) $(CFLAGS) s21_string.c s21_sprintf.c s21_string_test.c -o test_string $(LIBS)
	./test_string

test_sprintf:
	$(CC) $(CFLAGS) s21_string.c s21_sprintf.c s21_sprintf_test.c -o test_sprintf $(LIBS)
	./test_sprintf

test: test_string test_sprintf

s21_string.a: s21_string.o s21_sprintf.o
	ar rcs s21_string.a s21_string.o s21_sprintf.o

gcov_report: clean
	@echo "Building tests with coverage..."
	$(CC) $(CFLAGS) s21_string.c s21_sprintf.c s21_string_test.c -o test_string1 $(LIBS)
	$(CC) $(CFLAGS) s21_string.c s21_sprintf.c s21_sprintf_test.c -o test_string2 $(LIBS)

	@echo "Running tests..."
	./test_string1
	./test_string2
	
	@echo "Generating HTML report..."
	@if command -v lcov >/dev/null 2>&1; then \
		lcov --capture --directory . --output-file coverage.info; \
		lcov --remove coverage.info '/usr/*' --output-file coverage.info; \
		genhtml coverage.info --output-directory report; \
		open report/index.html || xdg-open report/index.html || echo "Open report/index.html"; \
	else \
		echo "ERROR: Install lcov first!"; \
		echo "macOS: brew install lcov"; \
		echo "Linux: sudo apt install lcov"; \
		exit 1; \
	fi

clean:
	rm -rf *.o *.gcda *.gcno *.gcov coverage.info report test_string

.PHONY: report clean


rebuild: clean all

%.o: %.c
	$(CC) $(CFLAGS) -c $<