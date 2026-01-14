#ifndef UTILS_H
#define UTILS_H
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

void* to_upper(const char* str);
void* to_lower(const char* str);
void* insert(const char* src, const char* str, s21_size start_index);
void* trim(const char* src, const char* trim_chars);

#endif