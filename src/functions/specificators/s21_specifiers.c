#include "s21_specifiers.h"

int s21_specifier_f(char *buff, va_list args, Prototype prot) {
  if (prot.prec_number == -1) {
    prot.prec_number = 6;
  }
  if (prot.length == 'L') {
    long double a = va_arg(args, long double);
    s21_long_double_to_str(a, buff, prot.prec_number, prot.sharp_flag);
  } else {
    double a = va_arg(args, double);
    s21_long_double_to_str(a, buff, prot.prec_number, prot.sharp_flag);
  }
  return s21_strlen(buff);
}

int s21_specifier_o(char *buff, va_list args, Prototype prot) {
  if (prot.length == 'l') {
    unsigned long int num = va_arg(args, unsigned long int);
    if (num == 0 && prot.prec_number == 0 && prot.width_number == 0) {
      buff[0] = '\0';
    } else if (!(num == 0 && prot.prec_number == 0)) {
      s21_UDecInNumSys(buff, num, 8, 0);
    } else {
      buff[0] = ' ';
    }
  } else {
    unsigned int num = va_arg(args, unsigned int);
    if (num == 0 && prot.prec_number == 0 && prot.width_number == 0) {
      buff[0] = '\0';
    } else if (!(num == 0 && prot.prec_number == 0)) {
      s21_UDecInNumSys(buff, num, 8, 0);
    } else {
      buff[0] = ' ';
    }
  }

  return s21_strlen(buff);
}

int s21_specifier_u(char *buff, va_list args, Prototype prot) {
  if (prot.length == 'l') {
    unsigned long int num = va_arg(args, unsigned long int);
    if (num == 0 && prot.prec_number == 0 && prot.width_number == 0) {
      buff[0] = '\0';
    } else if (!(num == 0 && prot.prec_number == 0)) {
      s21_UDecInNumSys(buff, num, 10, 0);
    } else {
      buff[0] = ' ';
    }
  } else {
    unsigned int num = va_arg(args, unsigned int);
    if (num == 0 && prot.prec_number == 0 && prot.width_number == 0) {
      buff[0] = '\0';
    } else if (!(num == 0 && prot.prec_number == 0)) {
      s21_UDecInNumSys(buff, num, 10, 0);
    } else {
      buff[0] = ' ';
    }
  }
  return s21_strlen(buff);
}

int s21_specifier_X(char *buff, va_list args, Prototype prot) {
  if (prot.length == 'l') {
    unsigned long int num = va_arg(args, unsigned long int);
    if (num == 0 && prot.prec_number == 0 && prot.width_number == 0) {
      buff[0] = '\0';
    } else if (!(num == 0 && prot.prec_number == 0)) {
      s21_UDecInNumSys(buff, num, 16, 1);
    } else {
      buff[0] = ' ';
    }
  } else {
    unsigned int num = va_arg(args, unsigned int);
    if (num == 0 && prot.prec_number == 0 && prot.width_number == 0) {
      buff[0] = '\0';
    } else if (!(num == 0 && prot.prec_number == 0)) {
      s21_UDecInNumSys(buff, num, 16, 1);
    } else {
      buff[0] = ' ';
    }
  }

  return s21_strlen(buff);
}

int s21_specifier_x(char *buff, va_list args, Prototype prot) {
  if (prot.length == 'l') {
    unsigned long int num = va_arg(args, unsigned long int);
    if (num == 0 && prot.prec_number == 0 && prot.width_number == 0) {
      buff[0] = '\0';
    } else if (!(num == 0 && prot.prec_number == 0)) {
      s21_UDecInNumSys(buff, num, 16, 0);
    } else {
      buff[0] = ' ';
    }
  } else {
    unsigned int num = va_arg(args, unsigned int);
    if (num == 0 && prot.prec_number == 0 && prot.width_number == 0) {
      buff[0] = '\0';
    } else if (!(num == 0 && prot.prec_number == 0)) {
      s21_UDecInNumSys(buff, num, 16, 0);
    } else {
      buff[0] = ' ';
    }
  }

  return s21_strlen(buff);
}

int s21_spec_p(va_list args, char *charbuf, Prototype *prot) {
  void *num = va_arg(args, void *);
  char buff[512] = {'\0'};
  long long int num2 = (long long int)num;
  if (num == S21_NULL) num2 = 0;
  int i = 0;
  s21_UDecInNumSys(buff, num2, 16, 0);

  int p_len = s21_strlen(buff);
  int space_len = 0;
  int zero_len = 0;
  if (prot->prec_number > p_len) zero_len = prot->prec_number - p_len;
  if (prot->width_number > p_len + zero_len + 2)
    space_len = prot->width_number - (p_len + zero_len + 2);

  if (prot->minus_flag != 1) {
    for (int k = 0; k < space_len; k++) {
      *(charbuf + i) = ' ';
      i++;
    };
  }

  s21_strcat(charbuf, "0x");
  i += 2;

  for (int k = 0; k < zero_len; k++) {
    *(charbuf + i) = '0';
    i++;
  };

  s21_strcat(charbuf, buff);
  i += p_len;
  if (prot->minus_flag == 1) {
    for (int k = 0; k < space_len; k++) {
      *(charbuf + i) = ' ';
      i++;
    };
  }
  return s21_strlen(charbuf);
}

void s21_spec_n(va_list args, int j) {
  int *var = va_arg(args, int *);
  *var = j;
}

int s21_spec_id(va_list args, Prototype *prot, char *charbuf) {
  __int128_t num = 0;
  int neg_flag = 0;
  if (prot->length == 'h') {
    num = (short)va_arg(args, int);
  } else if (prot->length == 'l') {
    num = va_arg(args, long int);
  } else {
    num = va_arg(args, int);
  };

  int num_i = 0;

  if (num < 0) {
    neg_flag = 1;
    num *= -1;
    charbuf[num_i] = '-';
    num_i = 1;
  }

  if (num == 0) {
    if (prot->prec_number == 0) {
      charbuf[num_i] = '\0';
      num_i++;
    } else {
      charbuf[num_i] = '0';
      num_i++;
    }

  } else {
    while (num > 0) {
      int tmp_dig = 0;
      tmp_dig = num % 10;
      num = num / 10;
      charbuf[num_i] = tmp_dig + '0';
      num_i++;
    }
  }

  s21_reverse(charbuf, neg_flag);
  return num_i;
}

int s21_spec_s(char *str, va_list args, Prototype *prot) {
  int i = 0;
  int len = 0;
  char *strng_arg = va_arg(args, char *);

  if (strng_arg == S21_NULL) {
    if (prot->prec_number == 0) {
      i += s21_prep_string(str, strng_arg, prot->prec_number, i);
    } else {
      s21_strncpy(str, "(null)", fmin(6, prot->prec_number));
    }
    return 2;
  }

  len = (int)s21_strlen(strng_arg);

  if (prot->prec_number < len && prot->prec_number != -1) {
    i += s21_prep_string(str, strng_arg, prot->prec_number, i);
  } else if (prot->prec_number == 0) {
    i += s21_prep_string(str, strng_arg, prot->prec_number, i);
  } else if (len <= prot->prec_number || prot->prec_number == -1) {
    i += s21_prep_string(str, strng_arg, len, i);
  }

  return i;
}

int s21_spec_c(char *str, va_list args, Prototype *prot) {
  char c = va_arg(args, int);
  int sp_qnt = 0;
  int i = 0;
  int ret = 0;
  if (prot->width_number > 0) {
    sp_qnt = prot->width_number - 1;
  };
  if (prot->minus_flag == 1) {
    str[i] = c;
    i++;
    i += s21_print_spaces(str, sp_qnt, i);
  } else {
    i += s21_print_spaces(str, sp_qnt, i);
    str[i] = c;
    i++;
  };
  if (c == 0) ret = -1;
  return ret;
}

int s21_spec_e(int counter_symbols_str, char *intermediate_str, va_list args,
               Prototype *prot) {
  int e = 0;
  long long int num_int = 0;
  int symbol = 0;
  int num_i = 0;
  char str_int[512] = {'\0'};
  char str_double[270] = {'\0'};
  char str_double_g[270] = {'\0'};
  char symbol_e = '\0';
  char str_degree[560] = {'\0'};
  bool flag_zero = false;
  bool flag_zero_negative = false;
  bool flag_zero_plus = false;
  bool flag_minus_num = false;
  bool flag_minus_num_g = false;
  bool check_num_i_g = false;
  bool flag_g = false;
  bool this_is_used = false;
  bool flag_g_prec_1 = true;
  bool prec_0 = false;
  int save_precision_g_1 = 0;
  int have_precision_g = 0;
  unsigned long int multiply = 1;
  int dont_write_number_with_point = 0;
  int check_g = 0;
  int precision = 6;
  int save_precision_for_rounding_g = 0;
  int save_multiply = 0;
  int save_degree = 0;
  unsigned long int multiply_for_fractional_num = 1;
  long int multiply_num_i_g = 1;
  int num_i_g = 0;
  double num = 0.;
  if (prot->length == 'L')
    num = va_arg(args, long double);
  else
    num = va_arg(args, double);
  double save_number_for_g = num;
  if (s21_check_arg(prot, intermediate_str, counter_symbols_str, num) != 0) {
    return counter_symbols_str;
  }
  if (prot->spec == 'g' || prot->spec == 'G') flag_g = true;
  if ((prot->spec == 'e' || prot->spec == 'E') && (num < 1 && num > 0.0) &&
      flag_zero_plus == false)
    flag_zero_plus = true;
  if ((prot->spec == 'g' || prot->spec == 'G') && (num < 1 && num > 0.0) &&
      flag_zero_plus == false)
    flag_zero_plus = true;
  if ((prot->spec == 'g' || prot->spec == 'G') && (num < 0))
    flag_minus_num_g = true;
  flag_zero_negative =
      s21_mantisssa_and_degree(&num, flag_zero, &num_int, &e, prot);
  if ((num_int == 0 || num_int == 1) &&
      (prot->spec == 'g' || prot->spec == 'G')) {
    if (num_int == 0) {
      str_int[0] = '0';
    } else
      str_int[0] = '1';
    s21_strcat(intermediate_str, str_int);
    return counter_symbols_str;
  }
  if (flag_g == true && 1 > e && e >= -4 &&
      (prot->prec_number == 1 || prot->prec_star == 1))
    flag_g_prec_1 = false;
  if (prot->prec_number == 0 || prot->prec_star == 0) {
    num = round(num * pow(10, 0)) / pow(10, 0);
    prec_0 = true;
  } else if ((prot->prec_number == 1 || prot->prec_star == 1) &&
             (flag_g_prec_1 = true) && (flag_g == true)) {
    num = round(num * pow(10, 0)) / pow(10, 0);
    if (num == 10) num /= 10;
  }
  s21_fractional_and_integer_part_of_a_number(
      &num_int, &num, prot, flag_zero_negative, flag_minus_num_g);
  dont_write_number_with_point = s21_rounding_and_precision_number(
      &num, &multiply, prot, &save_number_for_g, &e, &check_g, &precision,
      flag_zero_plus, flag_zero_negative, flag_g,
      &save_precision_for_rounding_g, this_is_used, &have_precision_g,
      &save_precision_g_1, &save_degree, &num_int);
  if (check_g != 1) {
    s21_writing_int_number_with_point(
        &num_int, &symbol, str_int, flag_zero_negative, &counter_symbols_str,
        &dont_write_number_with_point, &save_number_for_g, prot, &num_i_g,
        flag_minus_num, &have_precision_g, &save_precision_g_1, &save_degree,
        &e);
    counter_symbols_str = s21_concat_fractional_number_with_degree(
        num_i, counter_symbols_str, str_double, num, prot, symbol_e, e,
        str_degree, &dont_write_number_with_point);
    s21_check_fractional_number_for_zeros(&multiply, str_double, flag_minus_num,
                                          flag_g, this_is_used);
    bool point_is_not_here = false;
    if ((str_double[0] == 'e' || str_double[0] == 'E') &&
        prot->sharp_flag == 0 && flag_g == true) {
      int n = 0;
      point_is_not_here = true;
      for (; str_int[n] != '\0'; n++) {
      }
      if (str_int[n - 1] == '.') {
        n--;
        str_int[n] = '\0';
      }
    }
    if (prot->sharp_flag == 1 &&
        (str_double[0] == 'e' || str_double[0] == 'E')) {
      int i = 0;
      for (; str_int[i] != '\0'; i++) {
      }
      if (str_int[i - 1] == '.') {
        str_int[i] = '\0';
      } else {
        str_int[i] = '.';
        str_int[i + 1] = '\0';
      }
    }
    s21_strcat(str_int, str_double);  // соединяем 2 строки получаем число
    if (flag_g == true && prot->sharp_flag == 0 && point_is_not_here == false)
      s21_leading_zeros(str_int, &save_precision_g_1, &have_precision_g,
                        &check_g, prec_0);
    s21_strcat(intermediate_str,
               str_int);  // закидываем готовый результат в промежуточную строку
  } else {
    s21_writing_int_number_with_point(
        &num_int, &symbol, str_int, flag_zero_negative, &counter_symbols_str,
        &dont_write_number_with_point, &save_number_for_g, prot, &num_i_g,
        flag_minus_num, &have_precision_g, &save_precision_g_1, &save_degree,
        &e);
    save_multiply = multiply;
    precision++;
    s21_check_fractional_number_for_zeros(&multiply, str_double, flag_minus_num,
                                          flag_g, this_is_used);
    while (precision > 0 && multiply != 1) {
      precision--;
      save_multiply *= 10;
    }

    save_number_for_g *= save_multiply;
    if (num_i_g == 0) {
      while (precision > 0) {
        precision--;
        multiply_for_fractional_num *= 10;
      }
    } else
      num_i_g = precision - num_i_g;
    if (num_i_g != 0) {
      while (num_i_g > 0) {
        num_i_g--;
        multiply_num_i_g *= 10;
      }
      check_num_i_g = true;
    }
    s21_fractional_and_integer_part_of_a_number(&num_int, &save_number_for_g,
                                                prot, flag_zero_negative,
                                                flag_minus_num_g);
    if (save_multiply != 1) {
      multiply_num_i_g /= save_multiply;
      save_precision_for_rounding_g = 0;
    }
    if (num_i_g == 0 && check_num_i_g == false)
      save_number_for_g *= multiply_for_fractional_num;
    else {
      save_number_for_g *= multiply_num_i_g;
      save_number_for_g =
          round(save_number_for_g * pow(10, save_precision_for_rounding_g)) /
          pow(10, save_precision_for_rounding_g);
    }
    save_number_for_g = (long long int)save_number_for_g;
    s21_double_to_str(save_number_for_g, str_double_g, num_i);
    s21_reverse(str_double_g, 0);
    s21_strcat(str_double, str_double_g);
    s21_strcat(str_int, str_double);
    if (prot->sharp_flag == 0)
      s21_leading_zeros(str_int, &save_precision_g_1, &have_precision_g,
                        &check_g, prec_0);
    s21_strcat(intermediate_str, str_int);
  }
  return counter_symbols_str;
}