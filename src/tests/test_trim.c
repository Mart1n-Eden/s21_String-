#include "../suitecases.h"

START_TEST(trim_test1) {
  char *str1 = "";
  char *str2 = "";
  char *comp = "";
  char *res = s21_trim(str1, str2);
  ck_assert_str_eq(res, comp);
  if (res) free(res);
}
END_TEST

START_TEST(trim_test2) {
  char *str1 = "  \t\nHello World!   ";
  char *str2 = "";
  char *comp = "Hello World!";
  char *res = s21_trim(str1, str2);
  ck_assert_str_eq(res, comp);
  if (res) free(res);
}
END_TEST

START_TEST(trim_test3) {
  char *str1 = "a  \t\nHello World!   ";
  char *str2 = "";
  char *comp = "a  \t\nHello World!";
  char *res = s21_trim(str1, str2);
  ck_assert_str_eq(res, comp);
  if (res) free(res);
}
END_TEST

START_TEST(trim_test4) {
  char *str1 = "a  \t\nHello World!";
  char *str2 = "a!d";
  char *comp = "  \t\nHello Worl";
  char *res = s21_trim(str1, str2);
  ck_assert_str_eq(res, comp);
  if (res) free(res);
}
END_TEST

START_TEST(trim_test5) {
  char *str1 = "  \t\nHello World!   ";
  char *str2 = NULL;
  char *comp = "Hello World!";
  char *res = s21_trim(str1, str2);
  ck_assert_str_eq(res, comp);
  if (res) free(res);
}
END_TEST

START_TEST(trim_test6) {
  char *str1 = "123321312123!Hello World!ttterrrrr   ";
  char *str2 = "123!ter";
  char *comp = "Hello World!ttterrrrr   ";
  char *res = s21_trim(str1, str2);
  ck_assert_str_eq(res, comp);
  if (res) free(res);
}
END_TEST

Suite *suite_trim(void) {
  Suite *s = suite_create("suite_trim");
  TCase *tc = tcase_create("trim_tc");

  tcase_add_test(tc, trim_test1);
  tcase_add_test(tc, trim_test2);
  tcase_add_test(tc, trim_test3);
  tcase_add_test(tc, trim_test4);
  tcase_add_test(tc, trim_test5);
  tcase_add_test(tc, trim_test6);

  suite_add_tcase(s, tc);
  return s;
}