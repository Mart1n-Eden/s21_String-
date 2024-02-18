#include "../s21_sprintf.h"

int s21_read_format(Prototype *prot, const char *format, int i, va_list args) {
  int this_is_width = 0;
  int this_is_prec = 0;
  i++;
  while (format[i]) {
    s21_check_flags(format, i, prot, &this_is_prec, &this_is_width);
    s21_check_width(format, i, &this_is_width, prot, args);
    i = s21_check_prec(format, i, &this_is_prec, prot, args);
    if (format[i] == 'h') {
      prot->length = format[i];
    } else if (format[i] == 'l') {
      prot->length = format[i];
    } else if (format[i] == 'L') {
      prot->length = format[i];
    }
    // Check spec
    if (format[i] == 'c' || format[i] == 'd' || format[i] == 'i' ||
        format[i] == 'e' || format[i] == 'E' || format[i] == 'f' ||
        format[i] == 'g' || format[i] == 'G' || format[i] == 'o' ||
        format[i] == 's' || format[i] == 'u' || format[i] == 'x' ||
        format[i] == 'X' || format[i] == 'p' || format[i] == 'n' ||
        format[i] == '%')
      prot->spec = format[i];
    if (prot->spec == format[i])
      break;  // выходим нашелся спецификатор
    else
      i++;  // продолжаем дальше обрабатывать прототип спецификатора
  }
  return i;
}

int s21_check_prec(const char *format, int i, int *this_is_prec,
                   Prototype *prot, va_list args) {
  if (format[i] == '.') {
    i++;
    if (s21_check_number(format, i) == true && *this_is_prec == 0) {
      prot->prec_number = s21_write_number(format, &i);
      *this_is_prec = 1;
    } else if (format[i] == '*' && *this_is_prec == 0) {
      prot->prec_star = va_arg(args, int);
      prot->prec_number = prot->prec_star;
      *this_is_prec = 1;
    } else if (*this_is_prec == 0)
      prot->prec_number = 0;
  }
  return i;
}

void s21_check_width(const char *format, int i, int *this_is_width,
                     Prototype *prot, va_list args) {
  if (prot->width_number == 0 && format[i] == '*' && *this_is_width == 0) {
    prot->width_star = va_arg(args, int);
    *this_is_width = 1;
  }
  if (s21_check_number(format, i) == true && *this_is_width == 0) {
    prot->width_number = s21_write_number(format, &i);
    *this_is_width = 1;
  }
}

void s21_check_flags(const char *format, int i, Prototype *prot,
                     int *this_is_prec, int *this_is_width) {
  if (format[i] == '+') {
    prot->plus_flag = 1;
  } else if (format[i] == '-') {
    prot->minus_flag = 1;
  } else if (format[i] == ' ') {
    prot->space_flag = 1;
  } else if (format[i] == '#') {
    prot->sharp_flag = 1;
  } else if (format[i] == '0' && *this_is_prec == 0 && *this_is_width == 0) {
    prot->zero_flag = 1;
  }
}

bool s21_check_number(const char *format, int i) {
  bool result = false;
  if (format[i] >= '0' && format[i] <= '9') result = true;
  return result;
}

int s21_write_number(const char *format, int *i) {
  int width = 0;
  width += format[*i] - '0';
  *i += 1;
  while (s21_check_number(format, *i) == true) {
    width *= 10;
    width += format[*i] - '0';
    *i += 1;
  }
  return width;
}
