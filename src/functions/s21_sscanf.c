#include "../s21_string.h"

void getSFromStr(char** str_p, char* newStr, bool* isOK) {
  while (**str_p != ' ' && **str_p != '\t' && **str_p != '\n' &&
         **str_p != '\0') {
    *isOK = true;
    *(newStr++) = **str_p;
    (*str_p)++;
  }
  *newStr = '\0';
}

void propuskFirstRazdels(char** str_p) {
  while (**str_p == ' ' || **str_p == '\t' || **str_p == '\n') {
    (*str_p)++;
  }
}

bool isLetter(char* str_p) {
  if ((*str_p >= 'a' && *str_p <= 'f') || (*str_p >= 'A' && *str_p <= 'F')) {
    return true;
  } else
    return false;
}

void s21_strtol_pred(char** str_p, char*** str_endp, int* width, bool isWidth,
                     bool* isOK, bool* neg) {
  if (**str_p == '-') {
    *neg = true;
    (*width)--;
    (*str_p)++;
  } else if (**str_p == '+') {
    (*str_p)++;
    (*width)--;
  }
  if (**str_p == '0' && (isWidth == false || (isWidth == true && *width > 0))) {
    (*str_p)++;
    (*width)--;
    *isOK = true;
    if ((isWidth == false || (isWidth == true && *width > 0)) &&
        (**str_p == 'x' || **str_p == 'X')) {
      (*str_p)++;
      (*width)--;
    }
  }
  **str_endp = *str_p;
}

long long s21_strtol(char* str_p, char** str_endp, int basis, int width,
                     bool isWidth, bool* isOK, char dimension) {
  *str_endp = str_p;
  signed long long res = 0;
  bool neg = false;
  bool overflow = false;
  bool underflow = false;
  signed long long pastRes = res;
  s21_strtol_pred(&str_p, &str_endp, &width, isWidth, isOK,
                  &neg);  // чисто, чтобы
                          // освободить пространство
  while ((isWidth == false || (isWidth == true && width > 0)) &&
         *str_p >= '0' &&
         (*str_p <= ('0' + basis - 1) || (basis == 16 && isLetter(str_p)))) {
    *isOK = true;
    res *= basis;
    int num;
    if (isLetter(str_p) == false) {
      num = *str_p - '0';
    } else {
      num = *str_p - 'a' + 10;
      if (num < 0) num = *str_p - 'A' + 10;
    }
    if (neg == true) num *= -1;
    res += num;
    str_p++;
    width--;
    if (underflow == false && pastRes > 0 && res < pastRes) {
      overflow = true;
    } else if (overflow == false && pastRes < 0 && res > pastRes) {
      underflow = true;
    }
    pastRes = res;
  }
  *str_endp = str_p;
  switch (dimension) {
    case 'd':
      if (overflow == true) res = -1;
      break;
    case 'l':
      if (overflow == true) res = LLONG_MAX;
      if (underflow == true) res = LLONG_MIN;
      break;
    case 'h':
      if (overflow == true) res = -1;
      if (underflow == true) res = 0;
      break;
    case 'i':
      if (overflow == true) res = -1;
      if (underflow == true) res = 0;
      break;
  }
  return res;
}

bool isNANOrINF(char** str_p, long double* res, bool neg) {
  bool ret = false;
  if (s21_strncmp(*str_p, "nan", 3) == 0 ||
      s21_strncmp(*str_p, "NAN", 3) == 0) {
    *res = s21_NAN;
    if (neg == true) *res *= -1;
    ret = true;
  }
  if (s21_strncmp(*str_p, "inf", 3) == 0 ||
      s21_strncmp(*str_p, "INF", 3) == 0) {
    *res = s21_INF;
    if (neg == true) *res *= -1;
    ret = true;
  }
  if (ret == true) *(str_p) += 3;
  return ret;
}

void s21_strtod_pred(char** str_p, int* width, bool* isWidth, bool* isOK,
                     bool* neg, long double* res) {
  if (**str_p == '-') {
    *neg = true;
    (*width)--;
    (*str_p)++;
  } else if (**str_p == '+') {
    (*str_p)++;
    (*width)--;
  }
  if (isNANOrINF(str_p, res, neg) == true) {
    *isOK = true;
    *isWidth = true;  // чтобы быстренько смотаться
    *width = 0;       // из этой функции
  }
  while ((*isWidth == false || (*isWidth == true && *width > 0)) &&
         **str_p >= '0' && **str_p <= '9') {
    *isOK = true;
    *res *= 10;
    int num = **str_p - '0';
    if (*neg == true) {
      num *= -1;
    }
    *res += num;
    (*str_p)++;
    (*width)--;
  }
  if ((*isWidth == false || (*isWidth == true && *width > 0)) &&
      **str_p == '.') {
    long double fract = 0.1;
    (*str_p)++;
    (*width)--;
    while ((*isWidth == false || (*isWidth == true && *width > 0)) &&
           **str_p >= '0' && **str_p <= '9') {
      *isOK = true;
      int num = **str_p - '0';
      if (*neg == true) {
        num *= -1;
      }
      *res += num * fract;
      fract /= 10;
      (*str_p)++;
      (*width)--;
    }
  }
}

long double s21_strtod(char* str_p, char** str_endp, int width, bool isWidth,
                       bool* isOK) {
  long double res = 0;
  bool neg = false;
  s21_strtod_pred(&str_p, &width, &isWidth, isOK, &neg,
                  &res);  // чисто, чтобы
                          // освободить пространство
  if ((isWidth == false || (isWidth == true && width > 0)) && *str_p == 'e') {
    str_p++;
    width--;
    neg = false;
    bool isE = false;
    if (isWidth == false || (isWidth == true && width > 0)) {
      if (*str_p == '-') {
        neg = true;
        width--;
        str_p++;
      } else if (*str_p == '+') {
        str_p++;
        width--;
      }
    }
    int degree = 0;
    while ((isWidth == false || (isWidth == true && width > 0)) &&
           *str_p >= '0' && *str_p <= '9') {
      isE = true;
      degree *= 10;
      int num = *str_p - '0';
      if (neg == true) {
        num *= -1;
      }
      degree += num;
      str_p++;
      width--;
    }
    if (isE) res = res * pow(10, degree);
  }
  *str_endp = str_p;
  return res;
}

void sscanf_case_i(va_list* args, char** str_p, int width, bool isWidth,
                   bool* isOK, int* returnVal, char dimension,
                   bool* exitFromCycle) {
  propuskFirstRazdels(str_p);
  if ((**str_p == '0') ||
      (((**str_p == '+') || (**str_p == '-')) && *(*str_p + 1) == '0')) {
    if (*(*str_p + 1) == 'x' || *(*str_p + 1) == 'X' || *(*str_p + 2) == 'x' ||
        *(*str_p + 2) == 'X') {
      switch (dimension) {
        case 'l':
          *va_arg(*args, long*) =
              s21_strtol(*str_p, str_p, 16, width, isWidth, isOK, dimension);
          break;
        case 'h':
          *va_arg(*args, short*) =
              s21_strtol(*str_p, str_p, 16, width, isWidth, isOK, dimension);
          break;
        case 'i':
          *va_arg(*args, int*) =
              s21_strtol(*str_p, str_p, 16, width, isWidth, isOK, dimension);
          break;
      }

      if (*isOK == true) (*returnVal)++;
    } else {
      switch (dimension) {
        case 'l':
          *va_arg(*args, long*) =
              s21_strtol(*str_p, str_p, 8, width, isWidth, isOK, dimension);
          break;
        case 'h':
          *va_arg(*args, short*) =
              s21_strtol(*str_p, str_p, 8, width, isWidth, isOK, dimension);
          break;
        case 'i':
          *va_arg(*args, int*) =
              s21_strtol(*str_p, str_p, 8, width, isWidth, isOK, dimension);
          break;
      }
      if (*isOK == true) (*returnVal)++;
    }
  } else {
    switch (dimension) {
      case 'l':
        *va_arg(*args, long*) =
            s21_strtol(*str_p, str_p, 10, width, isWidth, isOK, dimension);
        break;
      case 'h':
        *va_arg(*args, short*) =
            s21_strtol(*str_p, str_p, 10, width, isWidth, isOK, dimension);
        break;
      case 'i':
        *va_arg(*args, int*) =
            s21_strtol(*str_p, str_p, 10, width, isWidth, isOK, dimension);
        break;
    }
    if (*isOK == true) (*returnVal)++;
  }
  if (isWidth == true && *isOK == false &&
      (*(*str_p - 1) == '+' || *(*str_p - 1) == '-')) {
    *exitFromCycle = true;
  }
}

void sscanf_case_d_o_u_x_X(va_list* args, char** str_p, int width, bool isWidth,
                           bool* isOK, int* returnVal, char dimension,
                           bool* exitFromCycle, int basis, bool suppress,
                           char format) {
  propuskFirstRazdels(str_p);
  if (!suppress) {
    switch (dimension) {
      case 'h':
        if (format == 'i' || format == 'd') {
          *va_arg(*args, signed short*) =
              s21_strtol(*str_p, str_p, basis, width, isWidth, isOK, dimension);
        } else {
          *va_arg(*args, unsigned short*) =
              s21_strtol(*str_p, str_p, basis, width, isWidth, isOK, dimension);
        }
        break;
      case 'd':
        if (format == 'i' || format == 'd') {
          *va_arg(*args, signed int*) =
              s21_strtol(*str_p, str_p, basis, width, isWidth, isOK, dimension);
        } else {
          *va_arg(*args, unsigned int*) =
              s21_strtol(*str_p, str_p, basis, width, isWidth, isOK, dimension);
        }
        break;
      case 'l':
        if (format == 'i' || format == 'd') {
          *va_arg(*args, signed long*) =
              s21_strtol(*str_p, str_p, basis, width, isWidth, isOK, dimension);
        } else {
          *va_arg(*args, unsigned long*) =
              s21_strtol(*str_p, str_p, basis, width, isWidth, isOK, dimension);
        }
        break;
    }
    if (*isOK == true) (*returnVal)++;
  } else {
    s21_strtol(*str_p, str_p, basis, width, isWidth, isOK, dimension);
  }
  if (isWidth == true && *isOK == false &&
      (*(*str_p - 1) == '+' || *(*str_p - 1) == '-')) {
    *exitFromCycle = true;
  }
}

void sscanf_case_e_e_f_g_G(va_list* args, char** str_p, int width, bool isWidth,
                           bool* isOK, int* returnVal, char dimension,
                           bool* exitFromCycle, bool suppress) {
  propuskFirstRazdels(str_p);
  if (!suppress) {
    switch (dimension) {
      case 'L':
        *va_arg(*args, long double*) =
            s21_strtod(*str_p, str_p, width, isWidth, isOK);
        break;
      case 'f':
        *va_arg(*args, float*) =
            s21_strtod(*str_p, str_p, width, isWidth, isOK);
        break;
    }
    if (*isOK == true) (*returnVal)++;
    if (*isOK == false) *exitFromCycle = true;
  } else {
    s21_strtod(*str_p, str_p, width, isWidth, isOK);
  }
}

int s21_sscanf(char* str, char* format, ...) {
  char *str_p = str, *format_p = format;
  va_list args;
  va_start(args, format);
  int returnVal = 0;
  bool isWidth = false;
  int width = 0;
  bool isOK = false;
  bool suppress = false;
  bool razdel = false;
  bool exitFromCycle =
      false;  // для кейса когда мы читаем только знак у числа из-за ширины и
              // после этого как бы сканф перестает работать
  bool minusOne = false;
  char* str_p_start =
      str_p;  // это нужно чтобы реализовать %n по примеру str_p - str_p_start
  while ((*format_p != '\0') && exitFromCycle == false) {
    if (*format_p == ' ' || *format_p == '\t' || *format_p == '\n') {
      razdel = true;
      format_p++;
      continue;
    }
    if (razdel == true && (*str_p == ' ' || *str_p == '\t' || *str_p == '\n')) {
      str_p++;
      continue;
    }
    if (*str_p == *format_p && *format_p != '%') {
      str_p++;
      format_p++;
      continue;
    }
    if (*format_p == '%') {
      width = 0;
      isWidth = false;
      suppress = false;
      razdel = false;
      format_p++;
      if (*format_p == '*') {
        suppress = true;
        format_p++;
      }
      isOK = false;
      if (*format_p >= '0' && *format_p <= '9') {
        width = s21_strtol(format_p, &format_p, 10, 0, false, &isOK, 'd');
        if (width > 0) isWidth = true;
      }
      isOK = false;
      if (*str_p == '\0' && *format_p != 'n' && *format_p != 'c' &&
          *format_p != 's') {
        exitFromCycle = true;
        minusOne = true;
        continue;
      }
      switch (*format_p) {
        case 'h':
          format_p++;
          switch (*format_p) {
            case 'i':
              sscanf_case_i(&args, &str_p, width, isWidth, &isOK, &returnVal,
                            'h', &exitFromCycle);
              break;
            case 'd':
              sscanf_case_d_o_u_x_X(&args, &str_p, width, isWidth, &isOK,
                                    &returnVal, 'h', &exitFromCycle, 10,
                                    suppress, 'd');
              break;
            case 'o':
              sscanf_case_d_o_u_x_X(&args, &str_p, width, isWidth, &isOK,
                                    &returnVal, 'h', &exitFromCycle, 8,
                                    suppress, 'o');
              break;
            case 'u':
              sscanf_case_d_o_u_x_X(&args, &str_p, width, isWidth, &isOK,
                                    &returnVal, 'h', &exitFromCycle, 10,
                                    suppress, 'u');
              break;
            case 'x':
            case 'X':
              sscanf_case_d_o_u_x_X(&args, &str_p, width, isWidth, &isOK,
                                    &returnVal, 'h', &exitFromCycle, 16,
                                    suppress, 'x');
              break;
          }
          break;
        case 'l':
          format_p++;
          switch (*format_p) {
            case 'i':
              sscanf_case_i(&args, &str_p, width, isWidth, &isOK, &returnVal,
                            'l', &exitFromCycle);
              break;
            case 'd':
              sscanf_case_d_o_u_x_X(&args, &str_p, width, isWidth, &isOK,
                                    &returnVal, 'l', &exitFromCycle, 10,
                                    suppress, 'd');
              break;
            case 'o':
              sscanf_case_d_o_u_x_X(&args, &str_p, width, isWidth, &isOK,
                                    &returnVal, 'l', &exitFromCycle, 8,
                                    suppress, 'o');
              break;
            case 'u':
              sscanf_case_d_o_u_x_X(&args, &str_p, width, isWidth, &isOK,
                                    &returnVal, 'l', &exitFromCycle, 10,
                                    suppress, 'u');
              break;
            case 'x':
            case 'X':
              sscanf_case_d_o_u_x_X(&args, &str_p, width, isWidth, &isOK,
                                    &returnVal, 'l', &exitFromCycle, 16,
                                    suppress, 'x');
              break;
          }
          break;
        case 'L':
          format_p++;
          switch (*format_p) {
            case 'e':
            case 'E':
            case 'f':
            case 'g':
            case 'G':
              sscanf_case_e_e_f_g_G(&args, &str_p, width, isWidth, &isOK,
                                    &returnVal, 'L', &exitFromCycle, suppress);
              break;
          }
          break;
        case 'c':
          if (!suppress) {
            *va_arg(args, char*) = *str_p;
            returnVal++;
          }
          str_p++;
          break;
        case 'd':
          sscanf_case_d_o_u_x_X(&args, &str_p, width, isWidth, &isOK,
                                &returnVal, 'd', &exitFromCycle, 10, suppress,
                                'd');
          break;
        case 'o':
          sscanf_case_d_o_u_x_X(&args, &str_p, width, isWidth, &isOK,
                                &returnVal, 'd', &exitFromCycle, 8, suppress,
                                'o');
          break;
        case 'u':
          sscanf_case_d_o_u_x_X(&args, &str_p, width, isWidth, &isOK,
                                &returnVal, 'd', &exitFromCycle, 10, suppress,
                                'u');
          break;
        case 'x':
        case 'X':
          sscanf_case_d_o_u_x_X(&args, &str_p, width, isWidth, &isOK,
                                &returnVal, 'd', &exitFromCycle, 16, suppress,
                                'x');
          break;
        case 'i':
          sscanf_case_i(&args, &str_p, width, isWidth, &isOK, &returnVal, 'i',
                        &exitFromCycle);
          break;
        case 'e':
        case 'E':
        case 'f':
        case 'g':
        case 'G':
          sscanf_case_e_e_f_g_G(&args, &str_p, width, isWidth, &isOK,
                                &returnVal, 'f', &exitFromCycle, suppress);
          break;
        case 's':
          propuskFirstRazdels(&str_p);
          getSFromStr(&str_p, va_arg(args, char*), &isOK);
          if (isOK == true) returnVal++;
          break;
        case 'p':
          if (!suppress) {
            propuskFirstRazdels(&str_p);
            *va_arg(args, int**) =
                (int*)s21_strtol(str_p, &str_p, 16, width, isWidth, &isOK, 'd');
            if (isOK == true) returnVal++;
          } else {
            s21_strtol(str_p, &str_p, 16, width, isWidth, &isOK, 'd');
          }
          break;
        case 'n':
          if (!suppress) {
            propuskFirstRazdels(&str_p);
            *va_arg(args, int*) = str_p - str_p_start;
            isOK = true;
          }
          break;
        case '%':
          if (!suppress) {
            propuskFirstRazdels(&str_p);
            isOK = true;
          }
          str_p++;
          break;
      }
      if (!(isOK == false &&
            *str_p ==
                '\0')) {  // этот костыль нужен чтобы корректно обработать empty
        format_p++;
      } else {
        if (*format_p != 'n' && *format_p != 'c' &&
            *format_p != 's') {  // а этот, чтобы обработать n, c
                                 // или s при конце строки
          exitFromCycle = true;
          minusOne = true;
        } else {
          format_p++;
        }
      }
    } else {
      exitFromCycle = true;
    }
  }
  if (minusOne == true) {
    returnVal = -1;
  }
  va_end(args);
  return returnVal;
}
