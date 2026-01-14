#include "utils.h"

#include "s21_string.h"

void* to_upper(const char* str) {
  if (str == s21_NULL) return s21_NULL;
  size_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  char* res = malloc(len + 1);
  if (res == s21_NULL) return s21_NULL;

  for (s21_size i = 0; i < len; i++) {
    char c = str[i];
    if (c >= 'a' && c <= 'z') {
      res[i] = c - 32;
    } else {
      res[i] = c;
    }
  }
  res[len] = '\0';
  return res;
}

void* to_lower(const char* str) {
  if (str == s21_NULL) return s21_NULL;
  size_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  char* res = malloc(len + 1);
  if (res == s21_NULL) return s21_NULL;

  for (size_t i = 0; i < len; i++) {
    char c = str[i];
    if (c >= 'A' && c <= 'Z') {
      res[i] = c + 32;
    } else {
      res[i] = c;
    }
  }
  res[len] = '\0';
  return res;
}

void* insert(const char* src, const char* str, s21_size start_index) {
  if (src == s21_NULL || str == s21_NULL) {
    return s21_NULL;
  }
  s21_size str_len = s21_strlen(str);
  s21_size src_len = s21_strlen(src);

  if (start_index > src_len) start_index = src_len;

  char* result = malloc(str_len + src_len + 1);

  if (result == s21_NULL) return s21_NULL;

  s21_strncpy(result, src, start_index);
  result[start_index] = '\0';
  s21_strcat(result, str);
  s21_strcat(result, src + start_index);

  return result;
}

void* trim(const char* src, const char* trim_chars) {
  if (src == s21_NULL || trim_chars == s21_NULL) {
    return s21_NULL;
  }

  const char* start = src;
  while (*start != '\0' && s21_strchr(trim_chars, *start) != s21_NULL) {
    start++;
  }

  if (*start == '\0') {
    char* result = (char*)malloc(1);
    if (result != s21_NULL) {
      result[0] = '\0';
    }
    return result;
  }

  const char* end = src + s21_strlen(src) - 1;
  while (end >= start && s21_strchr(trim_chars, *end) != s21_NULL) {
    end--;
  }

  size_t result_len = end - start + 1;

  char* result = (char*)malloc(result_len + 1);
  if (result == s21_NULL) {
    return s21_NULL;
  }

  s21_strncpy(result, start, result_len);
  result[result_len] = '\0';

  return result;
}