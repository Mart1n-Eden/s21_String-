#include "sub_func.h"

#include "../../s21_string.h"

void s21_shift_str(char *str, int size) {
  for (int i = size - 1; i > 0; --i) {
    str[i] = str[i - 1];
  }
}

void s21_UDecInNumSys(char *buff, unsigned long long int n, int mes, int flag) {
  int size_ans = 0;
  char str[2];
  str[0] = 'a';
  str[1] = 'A';
  if (n == 0) {
    buff[size_ans++] = '0';
  } else {
    while (n != 0) {
      size_ans += 1;
      s21_shift_str(buff, size_ans);
      if (n % mes > 9) {
        buff[0] = n % mes - 10 + str[flag];
      } else {
        buff[0] = n % mes + '0';
      }
      n /= mes;
    }
  }
  buff[size_ans] = '\0';
}

int s21_rounding(char *str, int count_before_dot, int pres, int neg_flag,
                 int add_point, int index) {
  int trans = 1;
  for (int i = count_before_dot + pres - 1 + add_point + neg_flag; i > 0; --i) {
    if (str[i] != '.') {
      int a = str[i] - '0';
      str[i] = (a + trans) % 10 + '0';
      trans = (a + trans) / 10;
    }
  }

  if (trans == 1 && str[0] == '9') {
    s21_shift_str(str, count_before_dot + pres - 1 + add_point + neg_flag);
    str[1] = '0';
    str[0] = '1';
  } else if (trans == 1 && str[0] == '-') {
    s21_shift_str(str + 1, count_before_dot + pres + add_point + 1);
    str[1] = '1';
    index++;
  } else if (trans == 1) {
    str[0] = str[0] + 1;
  }

  return index;
}
void s21_long_double_to_str(long double num, char *str, int pres,
                            int sharp_flag) {
  int count_before_dot = 0, index = 0, neg_flag = 0;
  long double num1 = 0, num2 = num;
  if (num < 0) {
    str[index++] = '-';
    num *= -1;
    num2 *= -1;
    neg_flag = 1;
  }
  while (num >= 1) {
    num /= 10;
    count_before_dot++;
  }
  for (int i = 0; i < count_before_dot; ++i) {
    num *= 10;
    int y = (int)num;
    num1 = num1 * 10 + y;
    num -= y;
    str[index++] = y + '0';
  }

  if (count_before_dot == 0) {
    str[index++] = '0';
    count_before_dot = 1;
  }
  int add_point = 0;
  if (pres != 0 || sharp_flag == 1) {
    str[index++] = '.';
    add_point = 1;
  }
  num2 -= num1;
  int flag_bad = 0;
  if (num2 == 1.) {
    num2 = 0.;
    flag_bad = 1;
  }
  for (int i = 0; i < pres; ++i) {
    num2 *= 10;
    int y = (int)num2;
    num2 -= y;
    str[index++] = y + '0';
  }
  num2 *= 10;
  int y = (int)num2;
  if (y >= 5) {
    index =
        s21_rounding(str, count_before_dot, pres, neg_flag, add_point, index);
  }
  if (flag_bad == 1) {
    int trans = 1;
    for (int i = count_before_dot + neg_flag - 1; i > 0; --i) {
      if (str[i] != '.') {
        int a = str[i] - '0';
        str[i] = (a + trans) % 10 + '0';
        trans = (a + trans) / 10;
      }
    }
  }
  str[index] = '\0';
}

void *s21_reverse(char *str, int neg_flag) {
  if (str == NULL) return NULL;
  int bgn = 0;
  if (neg_flag == 1) bgn = 1;
  int end = s21_strlen(str) - 1;
  char temp;
  while (bgn < end) {
    temp = str[bgn];
    *(str + bgn) = *(str + end);
    *(str + end) = temp;
    bgn++;
    end--;
  }
  return str;
}

int s21_print_spaces(char *str, int n, int j) {
  for (int i = 0; i < n; i++) str[j + i] = ' ';
  return n;
}

int s21_prep_string(char *str, char *strng_arg, int n, int j) {
  for (int i = 0; i < n; i++) {
    str[j + i] = strng_arg[i];
  };
  return n;
}
