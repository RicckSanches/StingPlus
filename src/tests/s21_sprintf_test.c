#include <check.h>
#include <string.h>

#include "../s21_string.h"

#define BUFSIZE 1024

static void compare_format(const char *fmt, ...) {
  char stdbuf[BUFSIZE];
  char mybuf[BUFSIZE];
  va_list ap;
  va_start(ap, fmt);
  va_list ap_copy;
  va_copy(ap_copy, ap);
  
  int std_len = vsnprintf(stdbuf, BUFSIZE, fmt, ap);
  int my_len = s21_vsprintf(mybuf, fmt, ap_copy);
  
  va_end(ap_copy);
  va_end(ap);
  
  ck_assert_msg(std_len == my_len,
                "\nfmt: \"%s\"\nstd_len: %d\nmy_len: %d", fmt, std_len, my_len);
  ck_assert_msg(strcmp(stdbuf, mybuf) == 0,
                "\nfmt: \"%s\"\nstd: \"%s\"\nmy : \"%s\"", fmt, stdbuf, mybuf);
}

START_TEST(test_plain_text) {
  compare_format("hello world");
  compare_format("");
  compare_format("%%%%");
  compare_format("test %% test");
}
END_TEST

START_TEST(test_single_char) {
  compare_format("%c", 'A');
  compare_format("-%c-", 'Z');
  compare_format("%c%c%c", 'a', 'b', 'c');
  compare_format("%c", '\0');
  compare_format("%c", 0);
}
END_TEST

START_TEST(test_string_basic) {
  compare_format("%s", "test");
  compare_format("-%s-", "abc");
  compare_format("%s%s", "hello", "world");
  compare_format("%s", "");
}
END_TEST

START_TEST(test_string_null) {
  compare_format("%s", (char *)NULL);
}
END_TEST

START_TEST(test_string_precision) {
  compare_format("%.0s", "abc");
  compare_format("%.2s", "abc");
  compare_format("%.10s", "abc");
  compare_format("%.5s", "short");
  compare_format("%.1s", "long string");
}
END_TEST

START_TEST(test_string_width) {
  compare_format("%5s", "abc");
  compare_format("%-5s", "abc");
  compare_format("%10s", "test");
  compare_format("%-10s", "L");
  compare_format("%3s", "very long string");
}
END_TEST

START_TEST(test_int_basic) {
  compare_format("%d", 0);
  compare_format("%d", 1);
  compare_format("%d", -1);
  compare_format("%i", 42);
  compare_format("%i", -42);
}
END_TEST

START_TEST(test_int_limits) {
  compare_format("%d", INT_MAX);
  compare_format("%d", INT_MIN);
  compare_format("%d", 2147483647);
  compare_format("%d", -2147483648);
}
END_TEST

START_TEST(test_int_width) {
  compare_format("%5d", 42);
  compare_format("%-5d", 42);
  compare_format("%10d", 123);
  compare_format("%-10d", -123);
  compare_format("%3d", 9999);
}
END_TEST

START_TEST(test_int_flags) {
  compare_format("%+5d", 42);
  compare_format("%+5d", -42);
  compare_format("% 5d", 42);
  compare_format("% 5d", -42);
  compare_format("%05d", 42);
  compare_format("%05d", -42);
}
END_TEST

START_TEST(test_int_precision) {
  compare_format("%.5d", 42);
  compare_format("%.5d", -42);
  compare_format("%.0d", 0);
  compare_format("%.10d", 123);
}
END_TEST

START_TEST(test_unsigned_basic) {
  compare_format("%u", 0u);
  compare_format("%u", 42u);
  compare_format("%u", 4294967295u);
}
END_TEST

START_TEST(test_unsigned_width_precision) {
  compare_format("%5u", 42u);
  compare_format("%.5u", 42u);
  compare_format("%10.5u", 123u);
}
END_TEST

START_TEST(test_hex_basic) {
  compare_format("%x", 0u);
  compare_format("%x", 255u);
  compare_format("%x", 15u);
  compare_format("%X", 255u);
  compare_format("%X", 15u);
}
END_TEST

START_TEST(test_hex_flags) {
  compare_format("%#x", 255u);
  compare_format("%#X", 255u);
  compare_format("%#x", 0u);
  compare_format("%#x", 15u);
}
END_TEST

START_TEST(test_octal_basic) {
  compare_format("%o", 0u);
  compare_format("%o", 255u);
  compare_format("%o", 8u);
}
END_TEST

START_TEST(test_octal_flags) {
  compare_format("%#o", 255u);
  compare_format("%#o", 0u);
  compare_format("%#o", 8u);
}
END_TEST

START_TEST(test_pointer) {
  int x = 5;
  compare_format("%p", (void *)&x);
  compare_format("%p", (void *)NULL);
  char c = 'a';
  compare_format("%p", (void *)&c);
}
END_TEST

START_TEST(test_float_basic) {
  compare_format("%f", 3.1415926);
  compare_format("%f", 0.0);
  compare_format("%f", -3.14);
  compare_format("%f", 123.456);
}
END_TEST

START_TEST(test_float_precision) {
  compare_format("%.3f", 3.1415926);
  compare_format("%.0f", 3.1415926);
  compare_format("%.10f", 3.1415926);
  compare_format("%.2f", 123.456);
}
END_TEST

START_TEST(test_float_width) {
  compare_format("%8.3f", 3.1415926);
  compare_format("%10f", 123.456);
  compare_format("%-10f", 123.456);
  compare_format("%10.2f", 123.456);
}
END_TEST

START_TEST(test_float_flags) {
  compare_format("%+f", 3.14);
  compare_format("%+f", -3.14);
  compare_format("% f", 3.14);
  compare_format("% f", -3.14);
  compare_format("%#f", 3.0);
}
END_TEST

START_TEST(test_float_scientific) {
  compare_format("%e", 12345.6789);
  compare_format("%E", 12345.6789);
  compare_format("%.3e", 12345.6789);
  compare_format("%.3E", 12345.6789);
}
END_TEST

START_TEST(test_float_g) {
  compare_format("%g", 0.000123);
  compare_format("%G", 0.000123);
  compare_format("%g", 12345.6789);
  compare_format("%G", 12345.6789);
}
END_TEST

START_TEST(test_multiple_args) {
  compare_format("%d %s %c %u %x %f", 1, "abc", 'X', 5u, 255u, 2.5);
  compare_format("Number: %d, String: %s", 42, "test");
  compare_format("%c%d%s", 'A', 123, "test");
}
END_TEST

START_TEST(test_length_modifiers) {
  compare_format("%ld", 123456L);
  compare_format("%lu", 123456UL);
  compare_format("%hd", (short)123);
  compare_format("%hu", (unsigned short)123);
  compare_format("%Lf", 3.14159L);
}
END_TEST

START_TEST(test_percent) {
  compare_format("%%");
  compare_format("test%%test");
  compare_format("%d%%", 50);
  compare_format("%%%d%%", 42);
}
END_TEST

START_TEST(test_edge_cases) {
  compare_format("%d", 0);
  compare_format("%u", 0u);
  compare_format("%x", 0u);
  compare_format("%o", 0u);
  compare_format("%f", 0.0);
  compare_format("%s", "");
  compare_format("%c", 0);
}
END_TEST

Suite *s21_suite(void) {
  Suite *s = suite_create("s21_sprintf");
  TCase *tc = tcase_create("core");
  
  tcase_add_test(tc, test_plain_text);
  tcase_add_test(tc, test_single_char);
  tcase_add_test(tc, test_string_basic);
  tcase_add_test(tc, test_string_null);
  tcase_add_test(tc, test_string_precision);
  tcase_add_test(tc, test_string_width);
  tcase_add_test(tc, test_int_basic);
  tcase_add_test(tc, test_int_limits);
  tcase_add_test(tc, test_int_width);
  tcase_add_test(tc, test_int_flags);
  tcase_add_test(tc, test_int_precision);
  tcase_add_test(tc, test_unsigned_basic);
  tcase_add_test(tc, test_unsigned_width_precision);
  tcase_add_test(tc, test_hex_basic);
  tcase_add_test(tc, test_hex_flags);
  tcase_add_test(tc, test_octal_basic);
  tcase_add_test(tc, test_octal_flags);
  tcase_add_test(tc, test_pointer);
  tcase_add_test(tc, test_float_basic);
  tcase_add_test(tc, test_float_precision);
  tcase_add_test(tc, test_float_width);
  tcase_add_test(tc, test_float_flags);
  tcase_add_test(tc, test_float_scientific);
  tcase_add_test(tc, test_float_g);
  tcase_add_test(tc, test_multiple_args);
  tcase_add_test(tc, test_length_modifiers);
  tcase_add_test(tc, test_percent);
  tcase_add_test(tc, test_edge_cases);
  
  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  Suite *s = s21_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return failed == 0 ? 0 : 1;
}
