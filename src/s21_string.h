#ifndef S21_STRING_H

#define S21_STRING_H

#include <stdarg.h>
#include <ctype.h>

#define s21_size_t unsigned long long
#define s21_NULL (void*)0

s21_size_t s21_strlen(char *str);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);

int s21_sprintf(char *str, char *format, ...);

struct format_flags {
    int width;
    int precision;
    int has_minus;
    int has_plus;
    int has_space;
    int length;
    char type;
};


int process_format(va_list args, char* str,  char *format);
void process_spec(char* spec_result, char* spec, int spec_index, struct format_flags *spec_flags, va_list args);
void process_char(char* spec_result, char* spec, int spec_index, struct format_flags *spec_flags, char arg);
void process_int(char* spec_result, char* spec, int spec_index, struct format_flags *spec_flags);
void process_float(char* spec_result, char* spec, int spec_index, struct format_flags *spec_flags);
void process_string(char* spec_result, char* spec, int spec_index, struct format_flags *spec_flags);
void process_unint(char* spec_result, char* spec, int spec_index, struct format_flags *spec_flags);
int check_spec_end(char symbol, struct format_flags *spec_flags);
void process_letter(char symbol, struct format_flags *spec_flags);
void check_flag(char flag, struct format_flags *spec_flags);
void spec_reset(char* spec, int* spec_index, char* spec_result, struct format_flags *spec_flags);
#endif