#include <stdio.h>
#include <check.h>
#include "s21_string.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/* ========== s21_strchr ========== */
START_TEST(test_s21_strchr_basic) {
    char text[] = "Hello World";
    char* result_s21 = s21_strchr(text, 'W');
    char* result_std = strchr(text, 'W');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strchr_find_first_o) {
    char text[] = "Hello World";
    char* result_s21 = s21_strchr(text, 'o');
    char* result_std = strchr(text, 'o');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strchr_not_found) {
    char text[] = "Hello World";
    char* result_s21 = s21_strchr(text, 'k');
    char* result_std = strchr(text, 'k');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strchr_empty_string) {
    char text[] = "";
    char* result_s21 = s21_strchr(text, 'W');
    char* result_std = strchr(text, 'W');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strchr_find_space) {
    char text[] = "Hello World";
    char* result_s21 = s21_strchr(text, ' ');
    char* result_std = strchr(text, ' ');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strchr_find_null_terminator) {
    char text[] = "Hello";
    char* result_s21 = s21_strchr(text, '\0');
    char* result_std = strchr(text, '\0');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strchr_find_first_char) {
    char text[] = "Hello World";
    char* result_s21 = s21_strchr(text, 'H');
    char* result_std = strchr(text, 'H');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strchr_find_last_char) {
    char text[] = "Hello World";
    char* result_s21 = s21_strchr(text, 'd');
    char* result_std = strchr(text, 'd');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

/* ========== s21_strrchr ========== */
START_TEST(test_s21_strrchr_basic) {
    char text[] = "Hello World";
    char* result_s21 = s21_strrchr(text, 'o');
    char* result_std = strrchr(text, 'o');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strrchr_multiple_s) {
    char text[] = "mississippi";
    char* result_s21 = s21_strrchr(text, 's');
    char* result_std = strrchr(text, 's');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strrchr_not_found) {
    char text[] = "Hello World";
    char* result_s21 = s21_strrchr(text, 'z');
    char* result_std = strrchr(text, 'z');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strrchr_empty_string) {
    char text[] = "";
    char* result_s21 = s21_strrchr(text, 'a');
    char* result_std = strrchr(text, 'a');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strrchr_null_terminator) {
    char text[] = "Hello";
    char* result_s21 = s21_strrchr(text, '\0');
    char* result_std = strrchr(text, '\0');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strrchr_single_char) {
    char text[] = "aaaaa";
    char* result_s21 = s21_strrchr(text, 'a');
    char* result_std = strrchr(text, 'a');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strrchr_find_first_char) {
    char text[] = "abcde";
    char* result_s21 = s21_strrchr(text, 'a');
    char* result_std = strrchr(text, 'a');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strrchr_find_middle_char) {
    char text[] = "abcde";
    char* result_s21 = s21_strrchr(text, 'c');
    char* result_std = strrchr(text, 'c');
    ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

/* ========== s21_strlen ========== */
START_TEST(test_s21_strlen_basic) {
    char text[] = "Hello World";
    s21_size_t result_s21 = s21_strlen(text);
    size_t result_std = strlen(text);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strlen_empty) {
    char text[] = "";
    s21_size_t result_s21 = s21_strlen(text);
    size_t result_std = strlen(text);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strlen_single_char) {
    char text[] = "A";
    s21_size_t result_s21 = s21_strlen(text);
    size_t result_std = strlen(text);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strlen_spaces) {
    char text[] = "   ";
    s21_size_t result_s21 = s21_strlen(text);
    size_t result_std = strlen(text);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strlen_escape_chars) {
    char text[] = "\t\n";
    s21_size_t result_s21 = s21_strlen(text);
    size_t result_std = strlen(text);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strlen_long_string) {
    char text[] = "This is a very long string for testing purposes";
    s21_size_t result_s21 = s21_strlen(text);
    size_t result_std = strlen(text);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strlen_with_null_in_middle) {
    char text[] = "Hello\0World";
    s21_size_t result_s21 = s21_strlen(text);
    size_t result_std = strlen(text);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strlen_numbers) {
    char text[] = "1234567890";
    s21_size_t result_s21 = s21_strlen(text);
    size_t result_std = strlen(text);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strlen_special_chars) {
    char text[] = "!@#$%^&*()";
    s21_size_t result_s21 = s21_strlen(text);
    size_t result_std = strlen(text);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strlen_mixed) {
    char text[] = "Hello123!@#";
    s21_size_t result_s21 = s21_strlen(text);
    size_t result_std = strlen(text);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

/* ========== s21_strcspn ========== */
START_TEST(test_s21_strcspn_no_match) {
    char str1[] = "abcdefg";
    char str2[] = "xyz";
    s21_size_t result_s21 = s21_strcspn(str1, str2);
    size_t result_std = strcspn(str1, str2);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strcspn_match_first) {
    char str1[] = "abcdefg";
    char str2[] = "a";
    s21_size_t result_s21 = s21_strcspn(str1, str2);
    size_t result_std = strcspn(str1, str2);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strcspn_match_middle) {
    char str1[] = "abcdefg";
    char str2[] = "d";
    s21_size_t result_s21 = s21_strcspn(str1, str2);
    size_t result_std = strcspn(str1, str2);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strcspn_digits) {
    char str1[] = "hello123";
    char str2[] = "0123456789";
    s21_size_t result_s21 = s21_strcspn(str1, str2);
    size_t result_std = strcspn(str1, str2);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strcspn_empty_reject) {
    char str1[] = "abcdefg";
    char str2[] = "";
    s21_size_t result_s21 = s21_strcspn(str1, str2);
    size_t result_std = strcspn(str1, str2);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strcspn_empty_str) {
    char str1[] = "";
    char str2[] = "abc";
    s21_size_t result_s21 = s21_strcspn(str1, str2);
    size_t result_std = strcspn(str1, str2);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strcspn_both_empty) {
    char str1[] = "";
    char str2[] = "";
    s21_size_t result_s21 = s21_strcspn(str1, str2);
    size_t result_std = strcspn(str1, str2);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strcspn_match_last) {
    char str1[] = "abcdef";
    char str2[] = "f";
    s21_size_t result_s21 = s21_strcspn(str1, str2);
    size_t result_std = strcspn(str1, str2);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strcspn_vowels) {
    char str1[] = "programming";
    char str2[] = "aeiou";
    s21_size_t result_s21 = s21_strcspn(str1, str2);
    size_t result_std = strcspn(str1, str2);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strcspn_subset) {
    char str1[] = "abc";
    char str2[] = "abcde";
    s21_size_t result_s21 = s21_strcspn(str1, str2);
    size_t result_std = strcspn(str1, str2);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strcspn_space_and_excl) {
    char str1[] = "hello world!";
    char str2[] = " !";
    s21_size_t result_s21 = s21_strcspn(str1, str2);
    size_t result_std = strcspn(str1, str2);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strcspn_numbers_in_middle) {
    char str1[] = "test123";
    char str2[] = "0123456789";
    s21_size_t result_s21 = s21_strcspn(str1, str2);
    size_t result_std = strcspn(str1, str2);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strcspn_multiple_matches) {
    char str1[] = "abcdef";
    char str2[] = "cf";
    s21_size_t result_s21 = s21_strcspn(str1, str2);
    size_t result_std = strcspn(str1, str2);
    ck_assert_int_eq(result_s21, result_std);
}
END_TEST

/* ========== s21_strerror ========== */
START_TEST(test_s21_strerror_known_errors) {
    for (int i = 0; i <= 133; i++) {
        char* result_s21 = s21_strerror(i);
        char* result_std = strerror(i);
        ck_assert_str_eq(result_s21, result_std);
    }
}
END_TEST

START_TEST(test_s21_strerror_negative) {
    int errnum = -1;
    char* result_s21 = s21_strerror(errnum);
    char* result_std = strerror(errnum);
    ck_assert_str_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strerror_large_number) {
    int errnum = 9999;
    char* result_s21 = s21_strerror(errnum);
    char* result_std = strerror(errnum);
    ck_assert_str_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strerror_zero) {
    int errnum = 0;
    char* result_s21 = s21_strerror(errnum);
    char* result_std = strerror(errnum);
    ck_assert_str_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_s21_strerror_edge_cases) {
    // Test common error codes
    int error_codes[] = {EACCES, EAGAIN, EBADF, EEXIST, EINTR, 
                        EINVAL, EIO, ENOENT, ENOMEM, EPERM};
    int num_codes = sizeof(error_codes) / sizeof(error_codes[0]);
    
    for (int i = 0; i < num_codes; i++) {
        char* result_s21 = s21_strerror(error_codes[i]);
        char* result_std = strerror(error_codes[i]);
        ck_assert_str_eq(result_s21, result_std);
    }
}
END_TEST

/* ========== Test Suites ========== */
Suite* s21_strchr_suite(void) {
    Suite* s = suite_create("s21_strchr");
    TCase* tc = tcase_create("Core");
    
    tcase_add_test(tc, test_s21_strchr_basic);
    tcase_add_test(tc, test_s21_strchr_find_first_o);
    tcase_add_test(tc, test_s21_strchr_not_found);
    tcase_add_test(tc, test_s21_strchr_empty_string);
    tcase_add_test(tc, test_s21_strchr_find_space);
    tcase_add_test(tc, test_s21_strchr_find_null_terminator);
    tcase_add_test(tc, test_s21_strchr_find_first_char);
    tcase_add_test(tc, test_s21_strchr_find_last_char);
    
    suite_add_tcase(s, tc);
    return s;
}

Suite* s21_strrchr_suite(void) {
    Suite* s = suite_create("s21_strrchr");
    TCase* tc = tcase_create("Core");
    
    tcase_add_test(tc, test_s21_strrchr_basic);
    tcase_add_test(tc, test_s21_strrchr_multiple_s);
    tcase_add_test(tc, test_s21_strrchr_not_found);
    tcase_add_test(tc, test_s21_strrchr_empty_string);
    tcase_add_test(tc, test_s21_strrchr_null_terminator);
    tcase_add_test(tc, test_s21_strrchr_single_char);
    tcase_add_test(tc, test_s21_strrchr_find_first_char);
    tcase_add_test(tc, test_s21_strrchr_find_middle_char);
    
    suite_add_tcase(s, tc);
    return s;
}

Suite* s21_strlen_suite(void) {
    Suite* s = suite_create("s21_strlen");
    TCase* tc = tcase_create("Core");
    
    tcase_add_test(tc, test_s21_strlen_basic);
    tcase_add_test(tc, test_s21_strlen_empty);
    tcase_add_test(tc, test_s21_strlen_single_char);
    tcase_add_test(tc, test_s21_strlen_spaces);
    tcase_add_test(tc, test_s21_strlen_escape_chars);
    tcase_add_test(tc, test_s21_strlen_long_string);
    tcase_add_test(tc, test_s21_strlen_with_null_in_middle);
    tcase_add_test(tc, test_s21_strlen_numbers);
    tcase_add_test(tc, test_s21_strlen_special_chars);
    tcase_add_test(tc, test_s21_strlen_mixed);
    
    suite_add_tcase(s, tc);
    return s;
}

Suite* s21_strcspn_suite(void) {
    Suite* s = suite_create("s21_strcspn");
    TCase* tc = tcase_create("Core");
    
    tcase_add_test(tc, test_s21_strcspn_no_match);
    tcase_add_test(tc, test_s21_strcspn_match_first);
    tcase_add_test(tc, test_s21_strcspn_match_middle);
    tcase_add_test(tc, test_s21_strcspn_digits);
    tcase_add_test(tc, test_s21_strcspn_empty_reject);
    tcase_add_test(tc, test_s21_strcspn_empty_str);
    tcase_add_test(tc, test_s21_strcspn_both_empty);
    tcase_add_test(tc, test_s21_strcspn_match_last);
    tcase_add_test(tc, test_s21_strcspn_vowels);
    tcase_add_test(tc, test_s21_strcspn_subset);
    tcase_add_test(tc, test_s21_strcspn_space_and_excl);
    tcase_add_test(tc, test_s21_strcspn_numbers_in_middle);
    tcase_add_test(tc, test_s21_strcspn_multiple_matches);
    
    suite_add_tcase(s, tc);
    return s;
}

Suite* s21_strerror_suite(void) {
    Suite* s = suite_create("s21_strerror");
    TCase* tc = tcase_create("Core");
    
    tcase_add_test(tc, test_s21_strerror_known_errors);
    tcase_add_test(tc, test_s21_strerror_negative);
    tcase_add_test(tc, test_s21_strerror_large_number);
    tcase_add_test(tc, test_s21_strerror_zero);
    tcase_add_test(tc, test_s21_strerror_edge_cases);
    
    suite_add_tcase(s, tc);
    return s;
}

int main(void) {
    int number_failed = 0;
    SRunner* sr;
    
    sr = srunner_create(s21_strchr_suite());
    srunner_add_suite(sr, s21_strrchr_suite());
    srunner_add_suite(sr, s21_strlen_suite());
    srunner_add_suite(sr, s21_strcspn_suite());
    srunner_add_suite(sr, s21_strerror_suite());
    
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? 0 : 1;
}