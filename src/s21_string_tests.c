#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_strncmp_basic) {
  int a = s21_strncmp("hello", "world", 5);
  int b = strncmp("hello", "world", 5);
  const char* str1 = "hello";
  const char* str2 = "hello";

  ck_assert_int_eq(a, b);
  ck_assert_int_eq(s21_strncmp("", "", 1), strncmp("", "", 1));
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
  ck_assert_int_eq(s21_strncmp("abc", "xyz", 0), strncmp("abc", "xyz", 0));
  ck_assert_int_eq(s21_strncmp("abc", "abcd", 4), strncmp("abc", "abcd", 4));
  ck_assert_int_eq(s21_strncmp("abc", "abd", 3), strncmp("abc", "abd", 3));
}
END_TEST

START_TEST(test_strpbrk) {
  const char* test1 = "Hello world";
  const char* test2 = "jke";
  const char* test3 = "";

  ck_assert_ptr_eq(s21_strpbrk(test1, test2), strpbrk(test1, test2));
  ck_assert_ptr_eq(s21_strpbrk(test2, test3), strpbrk(test2, test3));
  ck_assert_ptr_eq(s21_strpbrk(test3, test2), strpbrk(test3, test2));
  ck_assert_ptr_eq(s21_strpbrk("abcdef", "f"), strpbrk("abcdef", "f"));
  ck_assert_ptr_eq(s21_strpbrk("xyz", "x"), strpbrk("xyz", "x"));
  ck_assert_ptr_eq(s21_strpbrk("hello", "123"), strpbrk("hello", "123"));
}
END_TEST

START_TEST(test_strstr) {
  const char* test1 = "Helloworld";
  const char* test2 = "world";
  const char* test3 = "";

  ck_assert_ptr_eq(s21_strstr(test1, test2), strstr(test1, test2));
  ck_assert_ptr_eq(s21_strstr(test1, test3), strstr(test1, test3));
  ck_assert_ptr_eq(s21_strstr(test3, test2), strstr(test3, test2));
  ck_assert_ptr_eq(s21_strstr("hi", "hello"), strstr("hi", "hello"));
  ck_assert_ptr_eq(s21_strstr("hello", "e"), strstr("hello", "e"));
  ck_assert_ptr_eq(s21_strstr("aaaaa", "aa"), strstr("aaaaa", "aa"));
}
END_TEST

START_TEST(test_strtok_only_token) {
  char test1[] = "Hello, world";
  char test2[] = ",,,hello,,,,world   world";
  char test3[] = "";
  char test4[] = ",hello,";

  ck_assert_ptr_eq(s21_strtok(test1, ", "), strtok(test1, ", "));
  ck_assert_ptr_eq(s21_strtok(test2, ", "), strtok(test2, ", "));
  ck_assert_ptr_eq(s21_strtok(test3, "!, "), strtok(test3, "!, "));
  ck_assert_ptr_eq(s21_strtok(test4, ","), strtok(test4, ","));
  ck_assert_ptr_eq(s21_strtok(test1, ""), strtok(test1, ""));
  ck_assert_ptr_eq(s21_strtok(",,,,,,", ","), strtok(",,,,,,", ","));
  ck_assert_ptr_eq(s21_strtok(test1, "!"), strtok(test1, "!"));
}
END_TEST

START_TEST(test_strtok_full) {
  char s21_str[] = ",,,hello,,,,world   world";
  char std_str[] = ",,,hello,,,,world   world";

  char* s21_tok = s21_strtok(s21_str, ", ");
  char* std_tok = strtok(std_str, ", ");
  while (s21_tok != s21_NULL && std_tok != NULL) {
    ck_assert_str_eq(s21_tok, std_tok);
    s21_tok = s21_strtok(s21_NULL, ", ");
    std_tok = strtok(NULL, ", ");
  }
}
END_TEST

START_TEST(test_memchr) {
  const void* test1 = "Hello world";
  const void* test2 = "";

  ck_assert_ptr_eq(s21_memchr(test1, 3, 11), memchr(test1, 3, 11));
  ck_assert_ptr_eq(s21_memchr(test2, 1, 1), memchr(test2, 1, 1));
  ck_assert_ptr_eq(s21_memchr("aaa", 'a', 0), memchr("aaa", 'a', 0));
  ck_assert_ptr_eq(s21_memchr("abcdef", 'f', 3), memchr("abcdef", 'f', 3));
}
END_TEST

Suite* s21_string_suite() {
  Suite* s = suite_create("s21_string");

  TCase* tc_strncmp = tcase_create("strncmp");
  TCase* tc_strpbrk = tcase_create("strpbrk");
  TCase* tc_strstr = tcase_create("strstr");
  TCase* tc_strtok = tcase_create("strtok");
  TCase* tc_memchr = tcase_create("memchr");

  tcase_add_test(tc_strncmp, test_strncmp_basic);
  suite_add_tcase(s, tc_strncmp);
  tcase_add_test(tc_strpbrk, test_strpbrk);
  suite_add_tcase(s, tc_strpbrk);
  tcase_add_test(tc_strstr, test_strstr);
  suite_add_tcase(s, tc_strstr);
  tcase_add_test(tc_strtok, test_strtok_only_token);
  tcase_add_test(tc_strtok, test_strtok_full);
  suite_add_tcase(s, tc_strtok);
  tcase_add_test(tc_memchr, test_memchr);
  suite_add_tcase(s, tc_memchr);

  return s;
}

int main() {
  Suite* s = s21_string_suite();
  SRunner* runner = srunner_create(s);

  srunner_run_all(runner, CK_VERBOSE);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failed == 0 ? 0 : 1;
}
