#ifndef S21_STRING_H_
#define S21_STRING_H_

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define s21_NULL ((void*)0)
#define s21_size unsigned long

typedef struct {
  bool flag_minus;
  bool flag_plus;
  bool flag_space;
  bool flag_zero;
  bool flag_hash;
  int width;
  int precision;
  bool precision_specified;
  char length;
  char specifier;
} s21_format_t;

int s21_sprintf(char *str, const char *format, ...);
int s21_vsprintf(char *str, const char *format, va_list args);

int s21_process_format(char **out, const char **fmt, va_list *args);

const char *s21_parse_format(const char *p, s21_format_t *fmt, va_list *args);
const char *s21_parse_flags(const char *p, s21_format_t *fmt);
const char *s21_parse_width(const char *p, s21_format_t *fmt, va_list *args);
const char *s21_parse_precision(const char *p, s21_format_t *fmt,
                                va_list *args);
const char *s21_parse_length(const char *p, s21_format_t *fmt);

int s21_format_value(char **out, const s21_format_t *fmt, va_list *args);
int s21_format_int(char **out, const s21_format_t *fmt, va_list *args);
int s21_format_unsigned(char **out, const s21_format_t *fmt, va_list *args);
int s21_format_octal(char **out, const s21_format_t *fmt, va_list *args);
int s21_format_hex(char **out, const s21_format_t *fmt, va_list *args);
int s21_format_pointer(char **out, const s21_format_t *fmt, va_list *args);
int s21_format_float(char **out, const s21_format_t *fmt, va_list *args);
int s21_format_string(char **out, const s21_format_t *fmt, va_list *args);
int s21_format_char(char **out, va_list *args);

s21_size s21_strlen(const char *str);
void s21_reverse(char *str, int len);
int s21_int_to_str(long long value, char *buf, int precision);
int s21_uint_to_base(unsigned long long value, char *buf, int base,
                     bool uppercase, int precision);
void s21_apply_width(char **out, const char *buf, int len,
                     const s21_format_t *fmt, char pad_with);
int s21_float_to_str(double value, char *buf, int precision);

void *s21_memcpy(void *dest, const void *src, s21_size n);
void *s21_memset(void *str, int c, s21_size n);
int s21_memcmp(const void *str1, const void *str2, s21_size n);
void *s21_memchr(const void *str, int c, s21_size n);

char *s21_strncpy(char *dest, const char *src, s21_size n);
char *s21_strncat(char *dest, const char *src, s21_size n);
int s21_strncmp(const char *str1, const char *str2, s21_size n);

char *s21_strchr(const char *str, int c);
char *s21_strrchr(const char *str, int c);
size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

char *s21_strerror(int errnum);

#endif
