#ifndef S21_STRING_H

#define S21_STRING_H

#define s21_size_t unsigned long long
#define s21_NULL (void*)0

int s21_strlen(char *str);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);

#endif