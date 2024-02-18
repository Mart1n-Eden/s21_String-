#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include <stdarg.h>
#include <stdbool.h>

#include "s21_flag_handler.h"
#include "s21_string.h"
#define PRECISION 6;

int s21_parser(char *str, const char *format, va_list args);
int s21_read_format(Prototype *prot, const char *format, int i, va_list args);
bool s21_check_number(const char *format, int i);
int s21_write_number(const char *format, int *i);
void s21_check_flags(const char *format, int i, Prototype *prot,
                     int *this_is_prec, int *this_is_width);
void s21_check_width(const char *format, int i, int *this_is_width,
                     Prototype *prot, va_list args);
int s21_check_prec(const char *format, int i, int *this_is_prec,
                   Prototype *prot, va_list args);
int s21_args_to_str(int j, char *str, Prototype *prot, va_list args);

char *s21_add_sign_or_space(char *buf_str, Prototype prot, int sign);

char *s21_main_func(char *str, Prototype *prot);

#endif