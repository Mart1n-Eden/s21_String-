#include "../suitecases.h"

START_TEST(insert_test1) {
  char *str1 = S21_NULL;
  char *str2 = S21_NULL;
  s21_size_t index = 0;
  char *comp = S21_NULL;
  char *res = s21_insert(str1, str2, index);
  ck_assert_pstr_eq(res, comp);
  if (res) free(res);
}
END_TEST

START_TEST(insert_test2) {
  char *str1 = "Hello World!";
  char *str2 = "";
  s21_size_t index = 0;
  char *comp = "Hello World!";
  char *res = s21_insert(str1, str2, index);
  ck_assert_pstr_eq(res, comp);
  if (res) free(res);
}
END_TEST

START_TEST(insert_test3) {
  char *str1 = "World!";
  char *str2 = "Hello ";
  s21_size_t index = 0;
  char *comp = "Hello World!";
  char *res = s21_insert(str1, str2, index);
  ck_assert_pstr_eq(res, comp);
  if (res) free(res);
}
END_TEST

START_TEST(insert_test4) {
  char *str1 = "Hello ";
  char *str2 = "World!";
  s21_size_t index = 6;
  char *comp = "Hello World!";
  char *res = s21_insert(str1, str2, index);
  ck_assert_pstr_eq(res, comp);
  if (res) free(res);
}
END_TEST

START_TEST(insert_test5) {
  char *str1 = "Hello  World!";
  char *str2 = "Hello";
  s21_size_t index = 6;
  char *comp = "Hello Hello World!";
  char *res = s21_insert(str1, str2, index);
  ck_assert_pstr_eq(res, comp);
  if (res) free(res);
}
END_TEST

START_TEST(insert_test6) {
  char *str1 = "";
  char *str2 = "Hello";
  s21_size_t index = 0;
  char *comp = "Hello";
  char *res = s21_insert(str1, str2, index);
  ck_assert_pstr_eq(res, comp);
  if (res) free(res);
}
END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc = tcase_create("insert_tc");

  tcase_add_test(tc, insert_test1);
  tcase_add_test(tc, insert_test2);
  tcase_add_test(tc, insert_test3);
  tcase_add_test(tc, insert_test4);
  tcase_add_test(tc, insert_test5);
  tcase_add_test(tc, insert_test6);

  suite_add_tcase(s, tc);
  return s;
}