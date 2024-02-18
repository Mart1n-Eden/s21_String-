#ifndef SRC_S21_SPECIFICATORS_
#define SRC_S21_SPECIFICATORS_

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

#include "../../s21_string.h"
#include "s21_spec_e_g.h"
#include "sub_func.h"

int s21_specifier_o(char *buff, va_list args, Prototype prot);
int s21_specifier_x(char *buff, va_list args, Prototype prot);
int s21_specifier_X(char *buff, va_list args, Prototype prot);
int s21_specifier_u(char *buff, va_list args, Prototype prot);
int s21_specifier_f(char *buff, va_list args, Prototype prot);

int s21_spec_c(char *str, va_list args, Prototype *prot);
int s21_spec_id(va_list args, Prototype *prot, char *charbuf);
void s21_spec_n(va_list args, int j);
int s21_spec_s(char *str, va_list args, Prototype *prot);
int s21_spec_p(va_list args, char *charbuf, Prototype *prot);

int s21_spec_e(int j, char *intermediate_str, va_list args, Prototype *prot);
#endif
