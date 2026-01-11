#include "s21_string.h"
#include <stdarg.h>
#include <ctype.h>

#include <string.h>

int s21_sprintf(char *str, char *format, ...) {
    va_list args;
    va_start(args, format);

    int result = process_format(args, str, format);

    va_end(args);
    return result;
}

int process_format(va_list args, char* str, char *format) {
    char result_str[100] = {0};
    int result_index = 0;

    char spec[100] = {0};
    int spec_index = 0;

    char spec_result[100] = {0};

    struct format_flags spec_flags;

    int writting_spec = 0;

    int counter = 0;

    for (char* c = format; *c; c++) {
       if (*c == '%') {
        writting_spec = 1;
       }
       else {
        if (writting_spec) {
            if (*c == '%') {
                result_str[result_index++] = *c;
                writting_spec = 0;
            }
            else {
                int is_spec_end = check_spec_end(*c, &spec_flags); 
                if (is_spec_end) {
                    writting_spec = 0;
                    process_spec(spec_result, spec, spec_index, &spec_flags, args);
                    if (s21_strlen(spec_result) == 1) {
                        result_str[result_index++] = spec_result[0];
                    }
                    spec_reset(spec, &spec_index, spec_result, &spec_flags);
                    // s21_strncat(result_str, spec_result, sizeof(result_str) - s21_strlen(result_str) - 1);
                }
                else {
                    spec[spec_index++] = *c;
                }
            }
        }
        else {
            result_str[result_index++] = *c;
        }
       }
       counter++;
    }

    strcpy(str, result_str); // ЗАМЕНИТТЬ !!! ! ФФАЫФЦА
    return counter;
}

void process_spec(char* spec_result, char* spec, int spec_index, struct format_flags *spec_flags, va_list args) {
    switch (spec_flags->type)
    {
    case 'c':
        int arg = va_arg(args, int);
        char symbol = (char)arg;
        process_char(spec_result, spec, spec_index, spec_flags, symbol);
        break;
    case 'd':
        process_int(spec_result, spec, spec_index, spec_flags);
        break;
    case 'f':
        process_float(spec_result, spec, spec_index, spec_flags);
        break;
    case 's':
        process_string(spec_result, spec, spec_index, spec_flags);
        break;
    case 'u':
        process_unint(spec_result, spec, spec_index, spec_flags);
        break;
    default:
        break;
    }
}   

void process_char(char* spec_result, char* spec, int spec_index, struct format_flags *spec_flags, char arg) {
    spec_result[0] = arg;
    spec_result[1] = '\0';
}

void process_int(char* spec_result, char* spec, int spec_index, struct format_flags *spec_flags) {
    return;
}

void process_float(char* spec_result, char* spec, int spec_index, struct format_flags *spec_flags) {
    int can_be_flag = 1;
    for (int i = 1; i < spec_index; i++) {
        if (can_be_flag) {
            check_flag(spec[i], spec_flags);
        }

        if ((isdigit(spec[i]))) {
            can_be_flag = 0;
            process_digit();
        }
        else {
            switch (spec[i]) {
                case '.':
                    process_dot();
                    break;
                default:
                    print_error();
                    break;
            }
        }
    }
}

void process_string(char* spec_result, char* spec, int spec_index, struct format_flags *spec_flags) {

}

void process_unint(char* spec_result, char* spec, int spec_index, struct format_flags *spec_flags) {

}

void process_digit() {
    return;
}

void process_dot() {
    return;
}

void print_error() {
    return;
}

int check_spec_end(char symbol, struct format_flags *spec_flags) {
    int result = 0;
    switch (symbol)
    {
        case 'c':
        case 'd':
        case 'f':
        case 's':
        case 'u':
            process_letter(symbol, spec_flags);
            result = 1;
            break;
        default:
            break;
    }
    return result;
}

void process_letter(char symbol, struct format_flags *spec_flags) {
    switch (symbol)
    {
    case 'c':
        spec_flags->type = 'c';
        break;
    case 'd':
        spec_flags->type = 'd';
        break;
    case 'f':
        spec_flags->type = 'f';
        break;
    case 's':
        spec_flags->type = 's';
        break;
    case 'u':
        spec_flags->type = 'u';
        break;
    default:
        break;
    }
}

void check_flag(char flag, struct format_flags *spec_flags) {
    switch (flag)
    {
    case '+':
        spec_flags->has_plus = 1;
        break;
    case '-':
        spec_flags->has_minus = 1;
        break;
    case ' ':
        spec_flags->has_space = 1;
        break;
    default:
        break;
    }
}

void spec_reset(char* spec, int* spec_index, char* spec_result, struct format_flags *spec_flags) {
    spec[0] = '\0';
    *spec_index = 0;
    spec_result[0] = '\0';
    spec_flags->type = '\0';
    spec_flags->width = 0;
    spec_flags->precision = 0;
    spec_flags->has_minus = 0;
    spec_flags->has_plus = 0;
    spec_flags->has_space = 0;
    spec_flags->length = 0;
}