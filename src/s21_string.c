#include "s21_string.h"

void* s21_memchr(const void* str, int c, s21_size_t n) {
  const unsigned char* pstr = str;
  unsigned char target = (unsigned char)c;
  for (s21_size_t i = 0; i < n; i++) {
    if (pstr[i] == target) {
      return (void*)(pstr + i);
    }
  }
  return s21_NULL;
}

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    unsigned char c1 = str1[i];
    unsigned char c2 = str2[i];
    if (result == 0) {
      if (c1 != c2) {
        result = c1 - c2;
      } else if (c1 == '\0') {
        result = 0;
      }
    }
  }
  return result;
}

#if 0
// TODO strlen заменить на s21_strlen
char* s21_strpbrk(const char* str1, const char* str2) {
  s21_size_t str1_len = strlen(str1);
  s21_size_t str2_len = strlen(str2);
  for (s21_size_t i = 0; i < str1_len; i++) {
    char c1 = str1[i];
    for (s21_size_t j = 0; j < str2_len; j++) {
      char c2 = str2[j];
      if (c1 == c2) return (char*)(str1 + i);
    }
  }
  return s21_NULL;
}
#endif

char* s21_strpbrk(const char* str1, const char* str2) {
  if (!str1 || !str2) return s21_NULL;
  while (*str1) {
    const char* pstr2 = str2;
    while (*pstr2) {
      if (*str1 == *pstr2) return (char*)str1;
      pstr2++;
    }
    str1++;
  }
  return s21_NULL;
}

// TODO strlen заменить на s21_strlen
char* s21_strstr(const char* haystack, const char* needle) {
  s21_size_t nl = strlen(needle);
  s21_size_t hl = strlen(haystack);
  char* result = s21_NULL;
  if (*needle == '\0') return (char*)haystack;
  if (*haystack == '\0') return s21_NULL;
  if (nl > hl) return s21_NULL;
  for (s21_size_t i = 0; i <= hl - nl; i++) {
    s21_size_t j = 0;
    while (needle[j] && haystack[i + j] == needle[j]) {
      j++;
    }
    if (needle[j] == '\0') {
      return (char*)(haystack + i);
    }
  }
  return s21_NULL;
}

// TODO заменить strchr на s21_strchr
char* s21_strtok(char* str, const char* delim) {
  static char* save = s21_NULL;
  char* token_start = s21_NULL;
  if (str != s21_NULL) {
    save = str;
  }
  if (save == s21_NULL || *save == '\0') {
    return s21_NULL;
  }
  while (*save && strchr(delim, *save) != s21_NULL) {
    save++;
  }
  if (*save == '\0') return s21_NULL;
  token_start = save;
  while (*save && strchr(delim, *save) == s21_NULL) {
    save++;
  }
  if (*save) {
    *save = '\0';
    save++;
  }
  return token_start;
}