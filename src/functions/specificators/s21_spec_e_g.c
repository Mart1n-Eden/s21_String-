#include "s21_spec_e_g.h"

#include "../../s21_string.h"

int s21_double_to_str(long double num, char *str_double, int num_i) {
  while (num > 0) {
    int num_double = 0;
    num_double = (long int)num % 10;
    str_double[num_i] = num_double + '0';
    num_i++;
    num /= 10;
    num = (unsigned long int)num;
  }
  return num_i;
}

int s21_isnan(double number) {
  int result = 0;
  if (number != number) {
    result = 1;
  }
  return result;
}

void s21_leading_zeros(char *str_int, int *save_precision_g_1,
                       int *have_precision_g, int *check_g, bool prec_0) {
  int counter_g_leading_zeros = 0;
  int counter_g_prec = 0;
  char str_degree_from_degree[1024] = {'\0'};
  bool this_is_zero = false;
  bool this_is_int = false;
  bool check_for_g = false;
  if (str_int[counter_g_prec] == '-' && str_int[counter_g_prec + 1] == '.') {
    counter_g_leading_zeros += 1;
    this_is_zero = true;
    this_is_int = true;
  } else if (str_int[counter_g_prec] == '-')
    counter_g_prec += 1;
  while (this_is_int == false && this_is_zero == false) {
    if (counter_g_prec < (int)s21_strlen(str_int) &&
        str_int[counter_g_prec] != '.') {
      counter_g_leading_zeros += 1;
      counter_g_prec += 1;
    } else {
      counter_g_prec += 1;
      this_is_int = true;
    }
  }
  if (*have_precision_g == 0) {
    *save_precision_g_1 = 6;
    *save_precision_g_1 -= counter_g_leading_zeros;
  } else
    *save_precision_g_1 -= counter_g_leading_zeros;
  for (int i = 1; i <= *save_precision_g_1; i++) {
    if (str_int[counter_g_prec] != '\0') counter_g_prec++;
  }
  counter_g_prec--;
  if (*check_g != 1) {
    check_for_g = true;
    str_degree_from_degree[0] = str_int[counter_g_prec + 1];
    str_degree_from_degree[1] = str_int[counter_g_prec + 2];
    int n = 3;
    int n_degree = 2;
    while (str_int[counter_g_prec + n] != '\0') {
      str_degree_from_degree[n_degree] = str_int[counter_g_prec + n];
      n++;
      n_degree++;
    }
  }
  bool this_is_not_zero = false;
  while (this_is_not_zero == false) {
    if (str_int[counter_g_prec] == '0') {
      counter_g_prec--;
    } else
      this_is_not_zero = true;
  }
  if (this_is_not_zero == true) {
    str_int[counter_g_prec + 1] = '\0';
    if (check_for_g == true && prec_0 == false)
      s21_strcat(str_int, str_degree_from_degree);
  }
}

int s21_check_arg(Prototype *prot, char *intermediate_str,
                  int counter_symbols_str, double num) {
  int flag_check_arg = 0;
  if (num == INFINITY || num == -INFINITY) {
    int counter = 0;
    if (num == -INFINITY) {
      intermediate_str[counter] = '-';
      counter++;
    }
    if (prot->spec == 'E' || prot->spec == 'G') {
      intermediate_str[counter] = 'I';
      intermediate_str[counter + 1] = 'N';
      intermediate_str[counter + 2] = 'F';
    } else {
      intermediate_str[counter] = 'i';
      intermediate_str[counter + 1] = 'n';
      intermediate_str[counter + 2] = 'f';
    }
    if (counter > 0)
      counter_symbols_str += 4;
    else
      counter_symbols_str += 3;
    return counter_symbols_str;
  }
  if (s21_isnan(num) == 1) {
    if (prot->spec == 'E' || prot->spec == 'G') {
      intermediate_str[0] = 'N';
      intermediate_str[1] = 'A';
      intermediate_str[2] = 'N';
    } else {
      intermediate_str[0] = 'n';
      intermediate_str[1] = 'a';
      intermediate_str[2] = 'n';
    }
    counter_symbols_str += 3;
    return counter_symbols_str;
  }
  return flag_check_arg;
}

bool s21_mantisssa_and_degree(double *num, bool flag_zero,
                              long long int *num_int, int *e, Prototype *prot) {
  bool flag_zero_negative = false;
  if (*num == 0) flag_zero = true;
  if ((prot->spec == 'e' || prot->spec == 'E') &&
      (*num > -1 && signbit(*num) && *num < 0.0))
    flag_zero_negative = true;
  if ((prot->spec == 'g' || prot->spec == 'G') &&
      (*num > -1 && signbit(*num) && *num < 0.0))
    flag_zero_negative = true;
  *num_int = (long long int)*num;  // целая часть дробного числа
  // Мантисса + подсчет степени
  if (*num >= 1 || *num <= -1 || flag_zero == true) {
    if ((*num_int >= 10 || *num_int <= -10)) {
      do {
        *num /= 10;
        *e += 1;
      } while (*num > 10 || *num < -10);
    }

  } else {
    do {
      *num *= 10;
      *e -= 1;
      *num_int = (int)*num;
    } while (*num_int == 0 && flag_zero == false);
  }
  return flag_zero_negative;
}
void s21_fractional_and_integer_part_of_a_number(long long int *num_int,
                                                 double *num, Prototype *prot,
                                                 bool flag_zero_negative,
                                                 bool flag_minus_num_g) {
  // Разбиваем дробное число на два интовых типа целое число и дробная часть
  // здесь фиксить баг с точностью 1
  *num_int = (long long int)*num;
  if (*num_int >= 0)
    *num -= *num_int;
  else {
    *num *= -1;
    *num += *num_int;
  }
  if ((prot->spec == 'g' || prot->spec == 'G') && flag_zero_negative == true &&
      flag_minus_num_g == true)
    *num *= -1;
}
int s21_rounding_and_precision_number(
    double *num, unsigned long int *multiply, Prototype *prot,
    double *save_number_for_g, int *e, int *check_g, int *precision,
    bool flag_zero_plus, bool flag_zero_negative, bool flag_g,
    int *save_precision_for_rounding_g, bool this_is_used,
    int *have_precision_g, int *save_precision_g_1, int *save_degree,
    long long int *num_int) {
  // Тут идет округление числа если точность задана в else будет вызываться
  // функция точности
  // если после знака запятой будет < 6 цифр, то нужно округлять
  long long int flag = -1;
  int dont_write_number_with_point = 0;
  int counter_g_minus_e = 0;
  int counter_g_plus_e = 0;
  int counter_g_final_precison = 0;
  int save_precision_g = -1;
  double check_fractional_num_from_zeros_g = 0;
  double check_fractional_num_g = 0;
  bool flag_g_e_more_minus_four = false;
  bool this_is_prec_with_zeros = false;
  bool skip = false;

  if (prot->prec_star != -1) {
    *precision = prot->prec_star;
    *save_precision_g_1 = *precision;
    *have_precision_g = 1;
  } else if (prot->prec_number != -1) {
    *precision = prot->prec_number;
    *save_precision_g_1 = *precision;
    *have_precision_g = 1;
  }
  *save_degree = *e;
  if ((prot->spec == 'g' || prot->spec == 'G') &&
      ((*e >= -4 && *e <= 5 && (*have_precision_g == 0)) ||
       (*precision > *e && *e >= -4 && *have_precision_g == 1))) {
    flag_g_e_more_minus_four = true;
    *num = *save_number_for_g;
    while (*e < 0) {
      *e += 1;
      counter_g_minus_e++;
    }
    if (counter_g_minus_e > 0) counter_g_final_precison = counter_g_minus_e;
  }
  if (flag_g_e_more_minus_four == true) {
    *num = *save_number_for_g;
    *check_g = 1;
  }
  if (prot->prec_number == 0 || prot->prec_star == 0) {
    dont_write_number_with_point = 1;
    if (prot->spec == 'g' || prot->spec == 'G') *save_number_for_g = *num_int;
  } else {
    if (prot->prec_number == -1 || prot->prec_star == -1) {
      if (prot->spec == 'g' || prot->spec == 'G') {
        *precision -= 1;
        save_precision_g = *precision;
      }
      if (counter_g_minus_e == 0 && flag_g_e_more_minus_four == true) {
        this_is_used = true;
        *precision += 1;
        flag = (int)*num;
        if (flag < 0) flag *= -1;
        while (flag > 0) {
          flag /= 10;
          counter_g_plus_e++;
        }
        check_fractional_num_g = *save_number_for_g;
        s21_fractional_and_integer_part_of_a_number(
            &flag, &check_fractional_num_g, prot, 0, 0);
        *precision -= counter_g_plus_e;
        check_fractional_num_g =
            round(check_fractional_num_g * pow(10, *precision)) /
            pow(10, *precision);
        check_fractional_num_from_zeros_g = *save_number_for_g;
        for (int i = 0; i < *precision; i++)
          check_fractional_num_from_zeros_g *= 10;
        if ((long long int)check_fractional_num_from_zeros_g % 10 != 0)
          this_is_prec_with_zeros = true;
        int counter = *precision;
        for (int i = 0; i < counter && this_is_prec_with_zeros == false; i++) {
          check_fractional_num_g *= 10;
          if ((long long int)check_fractional_num_g % 10 == 0) *precision -= 1;
        }
        *save_precision_for_rounding_g = *precision;
        flag = -1;
      }
      if (prot->length == 'L')
        *num = roundl(*num * pow(10, *precision + counter_g_final_precison)) /
               pow(10, *precision + counter_g_final_precison);
      else
        *num = round(*num * pow(10, *precision + counter_g_final_precison)) /
               pow(10, *precision + counter_g_final_precison);
      if (flag_g == true && *check_g == 0)
        *num = round(*num * pow(10, *precision + counter_g_final_precison)) /
               pow(10, *precision + counter_g_final_precison);
      if (this_is_used == true) {
        *save_number_for_g = *num;
      }
      for (int i = 0; i < *precision; i++) {
        *num *= 10;
        if (*num == 0) {
          skip = true;
        }
        flag = (long long int)*num;
        if ((flag_zero_negative == false && flag_zero_plus == false &&
             flag_g == true) &&
            flag % 10 == 0)
          *multiply *= 10;
        if (flag == 0) *multiply *= 10;
      }
      while (flag % 10 == 0 && skip == false) {
        *multiply /= 10;
        flag /= 10;
        flag = (long long int)flag;
      }
      if (this_is_used == true) {
        *precision = save_precision_g;  // сохранение точности
      }
      if (flag_g == true && *check_g == 0)
        *num = round(*num * pow(10, 0)) / pow(10, 0);
      if (*num < 0) *num = fabs(*num);
      *num = (unsigned long int)*num;  // получение дробного числа в виде инта
    }
  }
  return dont_write_number_with_point;
}
void s21_writing_int_number_with_point(
    long long int *num_int, int *symbol, char *str_int, bool flag_zero_negative,
    int *counter_symbols_str, int *dont_write_number_with_point,
    double *save_number_for_g, Prototype *prot, int *num_i_g,
    bool flag_minus_num, int *have_precision_g, int *save_precision_g_1,
    int *save_degree, int *e) {
  // Записываем целое число в массив char в виде "-4." если целое число
  // отрицательное. "4." если число положительное
  bool check_g = false;
  double send_to_function_num = 0;
  if ((prot->spec == 'g' || prot->spec == 'G') &&
      ((*save_degree >= -4 && *save_degree <= 5 &&
        (prot->prec_number == -1 || prot->prec_star == -1)) ||
       (*save_precision_g_1 > *save_degree && *save_degree >= -4 &&
        (prot->prec_number != -1 || prot->prec_star != -1)))) {
    if (*save_precision_g_1 <= *e && *save_precision_g_1 != 0)
      *num_int = *num_int % 10;
    else
      *num_int = (long long int)*save_number_for_g;
    check_g = true;
  }
  if (check_g == true) {
    *symbol = *num_int;
    send_to_function_num = *symbol;
  } else
    *symbol = *num_int % 10;
  if (*dont_write_number_with_point == 1) {
    if (*symbol < 0) {
      *symbol *= -1;
      str_int[0] = '-';
      str_int[1] = *symbol + '0';
    } else
      str_int[0] = *symbol + '0';
  } else {
    if ((*symbol < 0 || flag_zero_negative == true) && check_g == false) {
      *symbol *= -1;
      str_int[0] = '-';
      str_int[1] = *symbol + '0';
      str_int[2] = '.';
      *counter_symbols_str += 3;
    } else {
      if (check_g == true) {
        *num_i_g = s21_double_to_str(send_to_function_num, str_int, 0);
        if (*num_i_g == 0 && send_to_function_num >= 0 &&
            flag_zero_negative == false) {
          str_int[0] = '0';
          str_int[1] = '.';
        } else {
          s21_reverse(str_int, 0);
          if (flag_zero_negative == false && send_to_function_num >= 0)
            str_int[*num_i_g] = '.';
        }
        if (flag_zero_negative == true) {
          send_to_function_num *= -1;
          str_int[0] = '-';
          str_int[1] = '0';
          str_int[2] = '.';
        }
        if ((*num_i_g == 0 && send_to_function_num < 0) &&
            flag_zero_negative == false) {
          unsigned long int counter = 10;
          flag_minus_num = true;
          send_to_function_num *= -1;
          *num_i_g = s21_double_to_str(send_to_function_num, str_int, 0);
          s21_reverse(str_int, 0);
          s21_check_fractional_number_for_zeros(&counter, str_int,
                                                flag_minus_num, 0, 0);
          str_int[*num_i_g + 1] = '.';
        }
        if ((*num_i_g == 6 && *have_precision_g == 0) ||
            (*num_i_g == *save_precision_g_1 && *have_precision_g == 1)) {
          if (str_int[0] == '-') *num_i_g += 1;
          str_int[*num_i_g] = '\0';
        }
      } else {
        str_int[0] = *symbol + '0';
        str_int[1] = '.';
        *counter_symbols_str += 2;
      }
    }
  }
}

int s21_concat_fractional_number_with_degree(
    int num_i, int counter_symbols_str, char *str_double, double num,
    Prototype *prot, char symbol_e, int e, char *str_degree,
    int *dont_write_number_with_point) {
  // Записываем дробную часть числа в массив char и соединяем дробную число
  // с степенью
  if (*dont_write_number_with_point != 1) {
    num_i = s21_double_to_str(num, str_double, num_i);
    s21_reverse(str_double, 0);
  }
  if (prot->spec == 'E' || prot->spec == 'G')
    symbol_e = 'E';
  else
    symbol_e = 'e';
  str_double[num_i] = symbol_e;
  counter_symbols_str++;
  if (e >= 0) {
    str_double[num_i + 1] = '+';
    counter_symbols_str++;
  }
  if (e < 0) {
    str_double[num_i + 1] = '-';
    counter_symbols_str++;
  }
  if (e >= 10) {
    s21_double_to_str(e, str_degree, 0);
    s21_reverse(str_degree, 0);
  } else {
    str_double[num_i + 2] = '0';
    counter_symbols_str++;
  }
  if (e == 0) {
    str_double[num_i + 3] = '0';
    counter_symbols_str++;
  } else {
    if (e < 0) e *= -1;
    s21_double_to_str(e, str_degree, 0);
    s21_reverse(str_degree, 0);
    s21_strcat(str_double, str_degree);  // соединяем число с степенью
  }
  return counter_symbols_str;
}

void s21_check_fractional_number_for_zeros(unsigned long int *multiply,
                                           char *str_double,
                                           bool flag_minus_num, bool flag_g,
                                           bool this_is_used) {
  // Проверка на то,что есть ли в дробной части нули
  (void)flag_g;
  (void)this_is_used;
  while (*multiply >= 10) {
    int check = s21_strlen(str_double) - 1;
    for (; check >= 0; check--) {
      str_double[check + 1] = str_double[check];
    }
    if (flag_minus_num == true) {
      str_double[0] = '-';
    } else
      str_double[0] = '0';
    *multiply /= 10;
  }
}