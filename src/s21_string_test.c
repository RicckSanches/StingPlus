#include <check.h>
#include <string.h>
#include <stdlib.h>

#include "./s21_string.h"

START_TEST(test_strlen) {
  ck_assert_uint_eq(s21_strlen("hello"), strlen("hello"));
  ck_assert_uint_eq(s21_strlen(""), strlen(""));
  ck_assert_uint_eq(s21_strlen("test string"), strlen("test string"));
}
END_TEST

START_TEST(test_memcpy) {
  char dest1[100], dest2[100];
  const char *src = "test";
  s21_memcpy(dest1, src, 5);
  memcpy(dest2, src, 5);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memset) {
  char str1[100], str2[100];
  s21_memset(str1, 'A', 10);
  memset(str2, 'A', 10);
  ck_assert_int_eq(memcmp(str1, str2, 10), 0);
}
END_TEST

START_TEST(test_memcmp) {
  ck_assert_int_eq(s21_memcmp("abc", "abc", 3), memcmp("abc", "abc", 3));
  ck_assert_int_eq(s21_memcmp("abc", "abd", 3), memcmp("abc", "abd", 3));
  ck_assert_int_eq(s21_memcmp("abd", "abc", 3), memcmp("abd", "abc", 3));
}
END_TEST

START_TEST(test_strncpy) {
  char dest1[100], dest2[100];
  const char *src = "test";
  s21_strncpy(dest1, src, 5);
  strncpy(dest2, src, 5);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat) {
  char dest1[100] = "hello";
  char dest2[100] = "hello";
  const char *src = " world";
  s21_strncat(dest1, src, 6);
  strncat(dest2, src, 6);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strchr) {
  const char *str = "hello";
  ck_assert_ptr_eq(s21_strchr(str, 'e'), strchr(str, 'e'));
  ck_assert_ptr_eq(s21_strchr(str, 'o'), strchr(str, 'o'));
  ck_assert_ptr_eq(s21_strchr(str, 'x'), strchr(str, 'x'));
}
END_TEST

START_TEST(test_strrchr) {
  const char *str = "hello";
  ck_assert_ptr_eq(s21_strrchr(str, 'l'), strrchr(str, 'l'));
  ck_assert_ptr_eq(s21_strrchr(str, 'o'), strrchr(str, 'o'));
  ck_assert_ptr_eq(s21_strrchr(str, 'x'), strrchr(str, 'x'));
}
END_TEST

START_TEST(test_strcspn) {
  ck_assert_uint_eq(s21_strcspn("hello", "l"), strcspn("hello", "l"));
  ck_assert_uint_eq(s21_strcspn("hello", "x"), strcspn("hello", "x"));
  ck_assert_uint_eq(s21_strcspn("test", "e"), strcspn("test", "e"));
}
END_TEST

START_TEST(test_memchr) {
  const char *str = "hello";
  ck_assert_ptr_eq(s21_memchr(str, 'e', 5), memchr(str, 'e', 5));
  ck_assert_ptr_eq(s21_memchr(str, 'o', 5), memchr(str, 'o', 5));
  ck_assert_ptr_eq(s21_memchr(str, 'x', 5), memchr(str, 'x', 5));
}
END_TEST

START_TEST(test_strncmp) {
  ck_assert_int_eq(s21_strncmp("abc", "abc", 3), strncmp("abc", "abc", 3));
  ck_assert_int_eq(s21_strncmp("abc", "abd", 3), strncmp("abc", "abd", 3));
  ck_assert_int_eq(s21_strncmp("abd", "abc", 3), strncmp("abd", "abc", 3));
}
END_TEST

START_TEST(test_strpbrk) {
  const char *str = "hello";
  ck_assert_ptr_eq(s21_strpbrk(str, "l"), strpbrk(str, "l"));
  ck_assert_ptr_eq(s21_strpbrk(str, "x"), strpbrk(str, "x"));
  ck_assert_ptr_eq(s21_strpbrk(str, "ho"), strpbrk(str, "ho"));
}
END_TEST

START_TEST(test_strstr) {
  const char *haystack = "hello world";
  ck_assert_ptr_eq(s21_strstr(haystack, "world"), strstr(haystack, "world"));
  ck_assert_ptr_eq(s21_strstr(haystack, "hello"), strstr(haystack, "hello"));
  ck_assert_ptr_eq(s21_strstr(haystack, "test"), strstr(haystack, "test"));
}
END_TEST

START_TEST(test_strtok) {
  char str1[100] = "hello,world,test";
  char str2[100] = "hello,world,test";
  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_str_eq(token1, token2);
  
  token1 = s21_strtok(NULL, ",");
  token2 = strtok(NULL, ",");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_strerror) {
  char *err1 = s21_strerror(0);
  char *err2 = strerror(0);
  ck_assert_str_eq(err1, err2);
  free(err1);
  
  err1 = s21_strerror(2);
  err2 = strerror(2);
  ck_assert_str_eq(err1, err2);
  free(err1);
}
END_TEST

Suite *s21_string_suite(void) {
  Suite *s = suite_create("s21_string");
  TCase *tc = tcase_create("core");
  
  tcase_add_test(tc, test_strlen);
  tcase_add_test(tc, test_memcpy);
  tcase_add_test(tc, test_memset);
  tcase_add_test(tc, test_memcmp);
  tcase_add_test(tc, test_strncpy);
  tcase_add_test(tc, test_strncat);
  tcase_add_test(tc, test_strchr);
  tcase_add_test(tc, test_strrchr);
  tcase_add_test(tc, test_strcspn);
  tcase_add_test(tc, test_memchr);
  tcase_add_test(tc, test_strncmp);
  tcase_add_test(tc, test_strpbrk);
  tcase_add_test(tc, test_strstr);
  tcase_add_test(tc, test_strtok);
  tcase_add_test(tc, test_strerror);
  
  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  Suite *s = s21_string_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return failed == 0 ? 0 : 1;
}

