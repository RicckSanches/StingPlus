#ifndef S21_STRING
#define S21_STRING
#include <string.h> //! убрать потом
#define s21_size_t unsigned long
#define s21_NULL ((void*)0)

void* s21_memchr(const void *str, int c, s21_size_t n);
int s21_strncmp (const char* str1, const char* str2, s21_size_t n);
char* s21_strpbrk(const char* str1, const char* str2);
char* s21_strstr(const char* haystack, const char* needle);
char* s21_strtok(char* str, const char* delim);

#endif