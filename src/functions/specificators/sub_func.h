#ifndef SRC_SUB_FUNC_H_
#define SRC_SUB_FUNC_H_

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct {
  char spec;
  int minus_flag;
  int plus_flag;
  int space_flag;
  int zero_flag;
  int sharp_flag;
  int width_number;
  int width_star;
  int prec_number;
  int prec_star;
  char length;
} Prototype;
void s21_shift_str(char *str, int size);

void s21_UDecInNumSys(char *buff, unsigned long long int n, int mes, int flag);

void s21_long_double_to_str(long double num, char *str, int pres,
                            int sharp_flag);

void *s21_reverse(char *str, int neg_flag);

int s21_print_spaces(char *str, int n, int j);

int s21_prep_string(char *str, char *strng_arg, int n, int j);

int s21_check_arg(Prototype *prot, char *intermediate_str,
                  int counter_symbols_str, double num);

#endif