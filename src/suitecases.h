#ifndef SUITECASES_H
#define SUITECASES_H

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "s21_sprintf.h"
#include "s21_string.h"

Suite *s21_string_suite(void);

Suite *suite_memchr(void);
Suite *suite_memcmp(void);
Suite *suite_memcpy(void);
Suite *suite_memmove(void);
Suite *suite_memset(void);
Suite *suite_strcat(void);
Suite *suite_strchr(void);
Suite *suite_strcmp(void);
Suite *suite_strcpy(void);
Suite *suite_strcspn(void);
Suite *suite_strerror(void);
Suite *suite_strlen(void);
Suite *suite_strncat(void);
Suite *suite_strncmp(void);
Suite *suite_strncpy(void);

Suite *suite_strpbrk(void);
Suite *suite_strrchr(void);
Suite *suite_strspn(void);
Suite *suite_strstr(void);
Suite *suite_strtok(void);

Suite *suite_insert(void);
Suite *suite_to_upper(void);
Suite *suite_to_lower(void);
Suite *suite_trim(void);

Suite *test_sprintf_c(void);
Suite *test_sprintf_f(void);
Suite *test_sprintf_percent(void);
Suite *test_sprintf_n(void);
Suite *test_sprintf_signed_i(void);
Suite *test_sprintf_string(void);
Suite *test_sprintf_octal(void);
Suite *test_sprintf_g(void);
Suite *test_sprintf_e(void);
Suite *test_sprintf_pointer(void);
Suite *test_sprintf_signed(void);
Suite *test_sprintf_HEX(void);
Suite *test_sprintf_hex(void);
Suite *test_sprintf_unsigned(void);

Suite *test_sscanf_c(void);
Suite *test_sscanf_d(void);
Suite *test_sscanf_i(void);
Suite *test_sscanf_o(void);
Suite *test_sscanf_x(void);
Suite *test_sscanf_p(void);
Suite *test_sscanf_n(void);
Suite *test_sscanf_real(void);
Suite *test_sscanf_empty(void);

void run_tests(void);
void run_testcase(Suite *testcase);
#endif
