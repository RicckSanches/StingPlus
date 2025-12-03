#include "s21_string.h"

int s21_strlen(char *str) {
    int res = 0;
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
    int result;
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
