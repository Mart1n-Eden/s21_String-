#include "../suitecases.h"

START_TEST(to_upper_test1) {
  char str1[] = "helloworld";
  char str2[] = "HELLOWORLD";
  char *res = s21_to_upper(str1);
  ck_assert_pstr_eq(res, str2);
  if (res) free(res);
}
END_TEST

START_TEST(to_upper_test2) {
  char str1[] = "HelLLo WorlDD!";
  char str2[] = "HELLLO WORLDD!";
  char *res = s21_to_upper(str1);
  ck_assert_pstr_eq(res, str2);
  if (res) free(res);
}
END_TEST

START_TEST(to_upper_test3) {
  char str1[] = "123HelLLO *)+&^--+^$22234____ 12\neaSSSS";
  char str2[] = "123HELLLO *)+&^--+^$22234____ 12\nEASSSS";
  char *res = s21_to_upper(str1);
  ck_assert_pstr_eq(res, str2);
  if (res) free(res);
}
END_TEST

START_TEST(to_upper_test4) {
  char str1[] = "";
  char str2[] = "";
  char *res = s21_to_upper(str1);
  ck_assert_pstr_eq(res, str2);
  if (res) free(res);
}
END_TEST

START_TEST(to_upper_test5) {
  char *str1 = S21_NULL;
  char *str2 = S21_NULL;
  char *res = s21_to_upper(str1);
  ck_assert_pstr_eq(res, str2);
  if (res) free(res);
}
END_TEST

Suite *suite_to_upper(void) {
  Suite *s = suite_create("suite_to_upper");
  TCase *tc = tcase_create("to_upper_tc");

  tcase_add_test(tc, to_upper_test1);
  tcase_add_test(tc, to_upper_test2);
  tcase_add_test(tc, to_upper_test3);
  tcase_add_test(tc, to_upper_test4);
  tcase_add_test(tc, to_upper_test5);

  suite_add_tcase(s, tc);
  return s;
}