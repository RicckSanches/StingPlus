#ifndef STRING_C_H

#define STRING_C_H

#include <stdio.h>


typedef long unsigned s21_size_t;

char *s21_strchr(const char *str, int c);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strlen(const char *str);
s21_size_t s21_strcspn(const char *str1,const char *str2);
char *s21_strerror(int errnum);

#endif