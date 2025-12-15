#include "s21_string.h"
#include <stdarg.h>

s21_size_t s21_strlen(char *str) {
    s21_size_t res = 0;
    if (str != s21_NULL) {
        char *p = str;
        while (*p != '\0') p++;
        res = p - str;
    } else {
        res = -1;
    }

    return res;
}


void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    unsigned char* d = (unsigned char*) dest;
    unsigned char* s = (unsigned char*) src;

    for (s21_size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    unsigned char* string = str;
    unsigned char symbol = c;
    for (s21_size_t i = 0; i < n; i++) {
        string[i] = symbol;
    }
    return str;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int result = 0;
    int are_equal = 1;
    const unsigned char* string1 = str1;
    const unsigned char* string2 = str2;

    for (s21_size_t i = 0; i < n && are_equal; i++) {
        if (string1[i] != string2[i]) {
            result = string1[i] - string2[i];
            are_equal = 0;
        }
    }
    return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    int is_end = 0;
    for (s21_size_t i = 0; i < n && !is_end; i++) {
        if (src[i] != '\0') {
            dest[i] = src[i];
        }
        else {
            dest[i] = '\0';
            is_end = 1;
        }
    }
    return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    s21_size_t dest_len = s21_strlen(dest);
    for (s21_size_t i = 0; i < n; i++) {
        dest[dest_len+i] = src[i];
    }
    return dest;
}


int s21_sprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char* spec[100] = {0};
    int spec_index = 0;

    char* result[100] = {0};
    int result_index = 0;

    int writting_spec = 0;

    for (char* c = format; *c; c++) {
        if (writting_spec) {
            if (*c == ' ' || *c == '\n' || *c == '\t') {
                writting_spec = 0;
                char* spec_result[100] = {0};
                process_spec(spec_result, spec, spec_index);
                
                for (s21_size_t i = 0; i < s21_strlen(spec_result); i++) {
                    result[result_index++] = spec_result[i];
                }
            }
            else {
                spec[spec_index++] = *c;
            }
        } 
        else if (*c != '%') {
            result[result_index++] =  *c;
        }
        else {
            writting_spec = 1;
            spec[spec_index++] = *c;
        }
    }
    va_end(args);
    return s21_strlen(str);
}


void process_spec(char* spec_string, char* spec, int spec_index) {
    for (int i = 1; i < spec_index; i++) {
        switch (spec[i])
        {
        case '2':
            /* code */
            break;
        
        default:
            break;
        }
    }
}