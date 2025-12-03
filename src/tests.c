#include <stdio.h>
#include <check.h>
#include "s21_string.h"
#include <string.h>
#include <stdlib.h>

START_TEST(test_s21_memcpy_basic) {
    char src[20] = "Hello friend";
    char d1[20] = {0};
    char d2[20] = {0};

    s21_memcpy(d1, src, 12);
    memcpy(d2, src, 12);

    ck_assert_mem_eq(d1, d2, 12);
}
END_TEST

START_TEST(test_s21_memcpy_zero) {
    char src[20] = "Hello friend";
    char d1[20] = {0};
    char d2[20] = {0};

    s21_memcpy(d1, src, 0);
    memcpy(d2, src, 0);

    ck_assert_mem_eq(d1, d2, 12);
}
END_TEST

START_TEST(test_s21_memset_basic) {
    char d1[10];
    char d2[10];

    s21_memset(d1, 'h', 10);
    memset(d2, 'h', 10);

    ck_assert_mem_eq(d1, d2, 10);
}
END_TEST

START_TEST(test_s21_memcmp_equal) {
    char a[] = "test";
    char b[] = "test";
    int result1 = s21_memcmp(a, b, 4);
    int result2 = memcmp(a, b, 4);
    ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_s21_memcmp_diff) {
    char a[] = "testA";
    char b[] = "testB";
    ck_assert_int_eq(
        (s21_memcmp(a, b, 5) > 0),
        (memcmp(a, b, 5) > 0)
    );
}
END_TEST

START_TEST(test_s21_strncpy_basic) {
    char src[] = "hello";
    char d1[10] = {0};
    char d2[10] = {0};

    s21_strncpy(d1, src, 10);
    strncpy(d2, src, 10);

    ck_assert_mem_eq(d1, d2, 10);
}
END_TEST

START_TEST(test_s21_strncpy_short) {
    char src[] = "hi";
    char d1[4] = {0};
    char d2[4] = {0};

    s21_strncpy(d1, src, 4);
    strncpy(d2, src, 4);

    ck_assert_mem_eq(d1, d2, 4);
}
END_TEST

START_TEST(test_s21_strncat_basic) {
    char d1[20] = "Hello ";
    char d2[20] = "Hello ";
    char src[] = "world!";

    s21_strncat(d1, src, 6);
    strncat(d2, src, 6);

    ck_assert_str_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_strncat_partial) {
    char d1[20] = "Hi ";
    char d2[20] = "Hi ";
    char src[] = "there!";

    s21_strncat(d1, src, 3);
    strncat(d2, src, 3);

    ck_assert_str_eq(d1, d2);
}
END_TEST


Suite *s21_string_suite() {
    Suite *s = suite_create("s21_string");
    TCase *tc_memcpy = tcase_create("memcpy");
    TCase *tc_memset = tcase_create("memset");
    TCase *tc_memcmp = tcase_create("memcmp");
    TCase *tc_strncpy = tcase_create("strncpy");
    TCase *tc_strncat = tcase_create("strncat");

    // memcpy
    tcase_add_test(tc_memcpy, test_s21_memcpy_basic);
    tcase_add_test(tc_memcpy, test_s21_memcpy_zero);

    // memset 
    tcase_add_test(tc_memset, test_s21_memset_basic);

    // memcmp 
    tcase_add_test(tc_memcmp, test_s21_memcmp_equal);
    tcase_add_test(tc_memcmp, test_s21_memcmp_diff);

    // strncpy
    tcase_add_test(tc_strncpy, test_s21_strncpy_basic);
    tcase_add_test(tc_strncpy, test_s21_strncpy_short);

    // strncat 
    tcase_add_test(tc_strncat, test_s21_strncat_basic);
    tcase_add_test(tc_strncat, test_s21_strncat_partial);

    suite_add_tcase(s, tc_memcpy);
    suite_add_tcase(s, tc_memset);
    suite_add_tcase(s, tc_memcmp);
    suite_add_tcase(s, tc_strncpy);
    suite_add_tcase(s, tc_strncat);

    return s;
}

int main() {
    Suite *s = s21_string_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}