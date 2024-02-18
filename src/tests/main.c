#include "../s21_string.h"
#include "../suitecases.h"

void run_testcase(Suite *testcase) {
  SRunner *runner = srunner_create(testcase);
  srunner_run_all(runner, CK_NORMAL);
  srunner_free(runner);
}

void run_all_testcases() {
  Suite *list_cases[] = {suite_memchr(),
                         suite_memcmp(),
                         suite_memcpy(),
                         suite_memmove(),
                         suite_memset(),
                         suite_strcat(),
                         suite_strchr(),
                         suite_strcmp(),
                         suite_strncmp(),
                         suite_strcpy(),
                         suite_strncpy(),
                         suite_strcspn(),
                         suite_strerror(),
                         s21_string_suite(),
                         suite_strlen(),
                         suite_strpbrk(),
                         suite_strrchr(),
                         suite_strspn(),
                         suite_strstr(),
                         suite_strtok(),

                         suite_insert(),
                         suite_to_lower(),
                         suite_to_upper(),
                         suite_trim(),

                         test_sprintf_unsigned(),
                         test_sprintf_c(),
                         test_sprintf_f(),
                         test_sprintf_percent(),
                         test_sprintf_n(),
                         test_sprintf_signed_i(),
                         test_sprintf_string(),
                         test_sprintf_octal(),
                         test_sprintf_g(),
                         test_sprintf_e(),
                         test_sprintf_pointer(),
                         test_sprintf_signed(),
                         test_sprintf_HEX(),
                         test_sprintf_hex(),
                         test_sprintf_unsigned(),

                         test_sscanf_c(),
                         test_sscanf_d(),
                         test_sscanf_i(),
                         test_sscanf_o(),
                         test_sscanf_x(),
                         test_sscanf_p(),
                         test_sscanf_n(),
                         test_sscanf_real(),
                         test_sscanf_empty(),

                         NULL};

  for (int i = 0; list_cases[i] != NULL; i++) {
    run_testcase(list_cases[i]);
  }
}

int main() {
  run_all_testcases();

  return 0;
}
