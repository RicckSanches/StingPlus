#include "utils.h"

START_TEST(test_to_upper_normal) {
  const char* input = "Hello World!";
  char* result = to_upper(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "HELLO WORLD!");
  free(result);
}
END_TEST

START_TEST(test_to_upper_empty) {
  const char* input = "";
  char* result = to_upper(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_to_upper_mixed) {
  const char* input = "Hello123 World!";
  char* result = to_upper(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "HELLO123 WORLD!");
  free(result);
}
END_TEST

START_TEST(test_to_upper_already_upper) {
  const char* input = "HELLO";
  char* result = to_upper(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "HELLO");
  free(result);
}
END_TEST

START_TEST(test_to_upper_null) {
  char* result = to_upper(NULL);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_to_upper_special_chars) {
  const char* input = "abc!@#def";
  char* result = to_upper(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "ABC!@#DEF");
  free(result);
}
END_TEST

START_TEST(test_to_lower_normal) {
  const char* input = "HELLO WORLD!";
  char* result = to_lower(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "hello world!");
  free(result);
}
END_TEST

START_TEST(test_to_lower_empty) {
  const char* input = "";
  char* result = to_lower(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_to_lower_mixed) {
  const char* input = "Hello123 WORLD!";
  char* result = to_lower(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "hello123 world!");
  free(result);
}
END_TEST

START_TEST(test_to_lower_already_lower) {
  const char* input = "hello";
  char* result = to_lower(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_to_lower_null) {
  char* result = to_lower(NULL);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_to_lower_special_chars) {
  const char* input = "ABC!@#DEF";
  char* result = to_lower(input);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "abc!@#def");
  free(result);
}
END_TEST

// ========== Тесты для insert ==========
START_TEST(test_insert_middle) {
  const char* src = "Hello World!";
  const char* insert_str = "Beautiful ";
  char* result = insert(src, insert_str, 6);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello Beautiful World!");
  free(result);
}
END_TEST

START_TEST(test_insert_beginning) {
  const char* src = "World!";
  const char* insert_str = "Hello ";
  char* result = insert(src, insert_str, 0);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello World!");
  free(result);
}
END_TEST

START_TEST(test_insert_end) {
  const char* src = "Hello";
  const char* insert_str = " World!";
  char* result = insert(src, insert_str, 5);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello World!");
  free(result);
}
END_TEST

START_TEST(test_insert_empty_src) {
  const char* src = "";
  const char* insert_str = "Hello";
  char* result = insert(src, insert_str, 0);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(test_insert_empty_insert_str) {
  const char* src = "Hello World!";
  const char* insert_str = "";
  char* result = insert(src, insert_str, 5);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello World!");
  free(result);
}
END_TEST

START_TEST(test_insert_null_src) {
  const char* insert_str = "Hello";
  char* result = insert(NULL, insert_str, 0);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_insert_null_str) {
  const char* src = "Hello";
  char* result = insert(src, NULL, 0);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_insert_out_of_bounds) {
  const char* src = "Hello";
  const char* insert_str = " World!";
  char* result = insert(src, insert_str, 100);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello World!");
  free(result);
}
END_TEST

START_TEST(test_insert_zero_length_at_end) {
  const char* src = "Hello";
  const char* insert_str = "!";
  char* result = insert(src, insert_str, 5);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello!");
  free(result);
}
END_TEST

// ========== Тесты для trim ==========
START_TEST(test_trim_both_sides) {
  const char* src = "  Hello World!  ";
  const char* trim_chars = " ";
  char* result = trim(src, trim_chars);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello World!");
  free(result);
}
END_TEST

START_TEST(test_trim_left_only) {
  const char* src = "  Hello World!";
  const char* trim_chars = " ";
  char* result = trim(src, trim_chars);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello World!");
  free(result);
}
END_TEST

START_TEST(test_trim_right_only) {
  const char* src = "Hello World!  ";
  const char* trim_chars = " ";
  char* result = trim(src, trim_chars);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello World!");
  free(result);
}
END_TEST

START_TEST(test_trim_multiple_chars) {
  const char* src = ".,.,Hello World!.,.";
  const char* trim_chars = ".,";
  char* result = trim(src, trim_chars);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello World!");
  free(result);
}
END_TEST

START_TEST(test_trim_no_trim_needed) {
  const char* src = "Hello World!";
  const char* trim_chars = " ";
  char* result = trim(src, trim_chars);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello World!");
  free(result);
}
END_TEST

START_TEST(test_trim_all_chars) {
  const char* src = "......";
  const char* trim_chars = ".";
  char* result = trim(src, trim_chars);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_empty_string) {
  const char* src = "";
  const char* trim_chars = " ";
  char* result = trim(src, trim_chars);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_null_src) {
  const char* trim_chars = " ";
  char* result = trim(NULL, trim_chars);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_trim_null_trim_chars) {
  const char* src = "Hello";
  char* result = trim(src, NULL);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_trim_mixed_chars) {
  const char* src = " \t\nHello\t\n ";
  const char* trim_chars = " \t\n";
  char* result = trim(src, trim_chars);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(test_trim_only_middle_spaces) {
  const char* src = "Hello   World";
  const char* trim_chars = " ";
  char* result = trim(src, trim_chars);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello   World");
  free(result);
}
END_TEST

Suite* string_utils_suite(void) {
  Suite* s = suite_create("String Utils");

  TCase* tc_upper = tcase_create("to_upper");
  tcase_add_test(tc_upper, test_to_upper_normal);
  tcase_add_test(tc_upper, test_to_upper_empty);
  tcase_add_test(tc_upper, test_to_upper_mixed);
  tcase_add_test(tc_upper, test_to_upper_already_upper);
  tcase_add_test(tc_upper, test_to_upper_null);
  tcase_add_test(tc_upper, test_to_upper_special_chars);
  suite_add_tcase(s, tc_upper);

  TCase* tc_lower = tcase_create("to_lower");
  tcase_add_test(tc_lower, test_to_lower_normal);
  tcase_add_test(tc_lower, test_to_lower_empty);
  tcase_add_test(tc_lower, test_to_lower_mixed);
  tcase_add_test(tc_lower, test_to_lower_already_lower);
  tcase_add_test(tc_lower, test_to_lower_null);
  tcase_add_test(tc_lower, test_to_lower_special_chars);
  suite_add_tcase(s, tc_lower);

  TCase* tc_insert = tcase_create("insert");
  tcase_add_test(tc_insert, test_insert_middle);
  tcase_add_test(tc_insert, test_insert_beginning);
  tcase_add_test(tc_insert, test_insert_end);
  tcase_add_test(tc_insert, test_insert_empty_src);
  tcase_add_test(tc_insert, test_insert_empty_insert_str);
  tcase_add_test(tc_insert, test_insert_null_src);
  tcase_add_test(tc_insert, test_insert_null_str);
  tcase_add_test(tc_insert, test_insert_out_of_bounds);
  tcase_add_test(tc_insert, test_insert_zero_length_at_end);
  suite_add_tcase(s, tc_insert);

  TCase* tc_trim = tcase_create("trim");
  tcase_add_test(tc_trim, test_trim_both_sides);
  tcase_add_test(tc_trim, test_trim_left_only);
  tcase_add_test(tc_trim, test_trim_right_only);
  tcase_add_test(tc_trim, test_trim_multiple_chars);
  tcase_add_test(tc_trim, test_trim_no_trim_needed);
  tcase_add_test(tc_trim, test_trim_all_chars);
  tcase_add_test(tc_trim, test_trim_empty_string);
  tcase_add_test(tc_trim, test_trim_null_src);
  tcase_add_test(tc_trim, test_trim_null_trim_chars);
  tcase_add_test(tc_trim, test_trim_mixed_chars);
  tcase_add_test(tc_trim, test_trim_only_middle_spaces);
  suite_add_tcase(s, tc_trim);

  return s;
}

int main(void) {
  int number_failed;
  Suite* s = string_utils_suite();
  SRunner* sr = srunner_create(s);

  srunner_set_log(sr, "test_results.log");
  srunner_set_tap(sr, "test_results.tap");

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}