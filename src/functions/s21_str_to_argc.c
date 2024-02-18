#include "../s21_sprintf.h"
int s21_args_to_str(int counter_symbols_str, char *str, Prototype *prot,
                    va_list args) {
  // В промежуточном массиве будет храниться строка без учета параметров
  // заданных в спецификаторе т.е флаги,ширина, точность и тд
  char intermediate_str[4096] = {'\0'};
  char *res = S21_NULL;
  int z = 0;
  if (prot->spec == 'c') {
    z = s21_spec_c(intermediate_str, args, prot);
    res = intermediate_str;
  } else if (prot->spec == 'd' || prot->spec == 'i') {
    s21_spec_id(args, prot, intermediate_str);
    res = s21_main_func(intermediate_str, prot);
  } else if (prot->spec == 's') {
    s21_spec_s(intermediate_str, args, prot);
    res = s21_main_func(intermediate_str, prot);
  } else if (prot->spec == 'n') {
    s21_spec_n(args, counter_symbols_str);
    res = intermediate_str;
  } else if (prot->spec == 'x') {
    s21_specifier_x(intermediate_str, args, *prot);
    res = s21_main_func(intermediate_str, prot);
  } else if (prot->spec == 'X') {
    s21_specifier_X(intermediate_str, args, *prot);
    res = s21_main_func(intermediate_str, prot);
  } else if (prot->spec == 'o') {
    s21_specifier_o(intermediate_str, args, *prot);
    res = s21_main_func(intermediate_str, prot);
  } else if (prot->spec == 'u') {
    s21_specifier_u(intermediate_str, args, *prot);
    res = s21_main_func(intermediate_str, prot);
  } else if (prot->spec == 'f') {
    s21_specifier_f(intermediate_str, args, *prot);
    res = s21_main_func(intermediate_str, prot);
  } else if (prot->spec == 'p') {
    s21_spec_p(args, intermediate_str, prot);
    res = intermediate_str;
  } else if (prot->spec == 'e' || prot->spec == 'E' || prot->spec == 'g' ||
             prot->spec == 'G') {
    s21_spec_e(counter_symbols_str, intermediate_str, args, prot);
    res = s21_main_func(intermediate_str, prot);
  }

  int index = 0;
  while (res[index] != '\0') {
    str[counter_symbols_str++] = res[index++];
  }
  str[counter_symbols_str] = '\0';
  if (prot->spec == 'f' || prot->spec == 'u' || prot->spec == 'o' ||
      prot->spec == 'X' || prot->spec == 'x' || prot->spec == 'd' ||
      prot->spec == 'i' || prot->spec == 's' || prot->spec == 'e' ||
      prot->spec == 'E' || prot->spec == 'g' || prot->spec == 'G') {
    free(res);
  }
  if (z == -1) {
    counter_symbols_str++;
  }

  return counter_symbols_str;
}
