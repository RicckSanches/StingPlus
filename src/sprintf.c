#include "s21_string.h"
#include <stdarg.h>

int s21_sprintf(char *str, const char *format, ...) {
    char specificators[5] = {'c', 'd', 'f', 's', 'u'};
    va_list args;
    va_start(args, format);

    char* spec[100] = {0};
    int spec_index = 0;

    char* result_str[100] = {0};
    int result_index = 0;

    char* spec_result[100] = {0};
    int writting_spec = 0;

    for (char* c = format; *c; c++) {
       if (*c == '%') {
        writting_spec = 1;
       }
       else {
        if (writting_spec) {
            int is_spec_end = check_spec_end();
            if (is_spec_end) {
                writting_spec = 0;
                process_spec(spec_result, spec, spec_index);
            }
            else {
                write_spec_symbol();
            }
        }
        else {
            result_str[result_index++] = *c;
        }
       }
    }

    va_end(args);
    return s21_strlen(str);
}


void process_spec(char* spec_result, char* spec, int spec_index) {
    for (int i = 1; i < spec_index; i++) {
        int is_digit = 0;

        for (int j = 1; j < 10; j++) {
            if (spec[i] == j) {
                is_digit = 1;
            }
        }

        if (is_digit) {
            process_digit();
        }
        else {
            switch (spec[i]) {
                case '.':
                    process_dot();
                    break;
                case 'd':
                case 'c':
                case 'f':
                case 's':
                case 'u':
                    process_letter();
                    break;
                case '+':
                    process_plus();
                    break;
                case '-':
                    process_minus();
                    break;
                case ' ':
                    process_space();
                    break;
                default:
                    print_error();
                    break;
            }
        }

        
    }
}   