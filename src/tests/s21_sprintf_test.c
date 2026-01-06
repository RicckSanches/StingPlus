
#include "../s21_string.h"

static void compare_format(const char *fmt, ...) {
  char stdbuf[1024];
  char mybuf[1024];
  va_list ap;
  va_start(ap, fmt);
  va_list ap_copy;
  va_copy(ap_copy, ap);
  vsprintf(stdbuf, fmt, ap);
  s21_vsprintf(mybuf, fmt, ap_copy);
  va_end(ap_copy);
  va_end(ap);
  ck_assert_msg(strcmp(stdbuf, mybuf) == 0,
                "\nfmt: \"%s\"\nstd: \"%s\"\nmy : \"%s\"", fmt, stdbuf, mybuf);
}

START_TEST(test_plain_text) {
  compare_format("hello world");
  compare_format("");
  compare_format("%%%%");
}
END_TEST

START_TEST(test_single_char) {
  compare_format("%c", 'A');
  compare_format("-%c-", 'Z');
}
END_TEST

START_TEST(test_string_basic) {
  compare_format("%s", "test");
  compare_format("-%s-", "abc");
}
END_TEST

START_TEST(test_string_null) { compare_format("%s", (char *)NULL); }
END_TEST

START_TEST(test_string_precision) {
  compare_format("%.0s", "abc");
  compare_format("%.2s", "abc");
  compare_format("%.10s", "abc");
}
END_TEST

START_TEST(test_int_basic) {
  compare_format("%d", 0);
  compare_format("%d", 1);
  compare_format("%d", -1);
}
END_TEST

START_TEST(test_int_limits) {
  compare_format("%d", INT_MAX);
  compare_format("%d", INT_MIN);
}
END_TEST

START_TEST(test_unsigned_hex_octal) {
  compare_format("%u %x %X %o", 42u, 255u, 255u, 255u);
}
END_TEST

START_TEST(test_width_precision_flags) {
  compare_format("%5d", 42);
  compare_format("%05d", 42);
  compare_format("%+5d", 42);
  compare_format("% 5d", 42);
  compare_format("%#x", 255);
  compare_format("%#o", 255);
  compare_format("%-10s", "L");
}
END_TEST

START_TEST(test_pointer) {
  int x = 5;
  compare_format("%p", (void *)&x);
}
END_TEST

START_TEST(test_float_basic) {
  compare_format("%f", 3.1415926);
  compare_format("%.3f", 3.1415926);
  compare_format("%8.3f", 3.1415926);
  compare_format("%e", 12345.6789);
  compare_format("%g", 0.000123);
}
END_TEST

START_TEST(test_multiple_args) {
  compare_format("%d %s %c %u %x %f", 1, "abc", 'X', 5u, 255u, 2.5);
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
  tcase_add_test(tc, test_int_basic);
  tcase_add_test(tc, test_int_limits);
  tcase_add_test(tc, test_unsigned_hex_octal);
  tcase_add_test(tc, test_width_precision_flags);
  tcase_add_test(tc, test_pointer);
  tcase_add_test(tc, test_float_basic);
  tcase_add_test(tc, test_multiple_args);
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
