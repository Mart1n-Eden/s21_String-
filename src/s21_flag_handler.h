#ifndef SRC_S21_FLAG_HANDLER_
#define SRC_S21_FLAG_HANDLER_

#include "functions/specificators/s21_specifiers.h"

char *s21_add_sign_or_space(char *buf_str, Prototype prot, int sign);

char *s21_main_func(char *str, Prototype *prot);

char *s21_add_char_left(char *str, int n, int str_size, char c, Prototype prot);
char *s21_add_char_right(char *str, int n, int str_size, char c);
char *s21_n_shift(char *str, int negativ_num, Prototype prot);
char *s21_add_sharp_sign(char *str, Prototype prot);

#endif