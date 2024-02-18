#ifndef SRC_S21_ARTEM_EG_H_
#define SRC_S21_ARTEM_EG_H_

#include "s21_specifiers.h"
#include "sub_func.h"

int s21_double_to_str(long double num, char *str_double, int num_i);
int s21_isnan(double number);
int s21_check_arg(Prototype *prot, char *intermediate_str,
                  int counter_symbols_str, double num);
bool s21_mantisssa_and_degree(double *num, bool flag_zero,
                              long long int *num_int, int *e, Prototype *prot);
void s21_fractional_and_integer_part_of_a_number(long long int *num_int,
                                                 double *num, Prototype *prot,
                                                 bool flag_zero_negative,
                                                 bool flag_minus_num_g);
int s21_rounding_and_precision_number(
    double *num, unsigned long int *multiply, Prototype *prot,
    double *save_number_for_g, int *e, int *check_g, int *precison,
    bool flag_zero_plus, bool flag_zero_negative, bool flag_g,
    int *save_precision_for_rounding_g, bool this_is_used,
    int *have_precision_g, int *save_precision_g, int *save_degree,
    long long int *num_int);
void s21_leading_zeros(char *str_int, int *save_precision_g_1,
                       int *have_precision_g, int *check_g, bool prec_0);
void s21_writing_int_number_with_point(
    long long int *num_int, int *symbol, char *str_int, bool flag_zero_negative,
    int *counter_symbols_str, int *dont_write_number_with_point,
    double *save_number_for_g, Prototype *prot, int *num_i_g,
    bool flag_minus_num, int *have_precision_g, int *save_precision_g,
    int *save_degree, int *e);
int s21_concat_fractional_number_with_degree(int num_i, int counter_symbols_str,
                                             char *str_double, double num,
                                             Prototype *prot, char symbol_e,
                                             int e, char *str_degree,
                                             int *dont_write_number_with_point);
void s21_check_fractional_number_for_zeros(unsigned long int *multiply,
                                           char *str_double,
                                           bool flag_minus_num, bool flag_g,
                                           bool this_is_used);

#endif