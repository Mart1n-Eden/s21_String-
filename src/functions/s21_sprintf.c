#include "../s21_sprintf.h"

#include "../s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  int result = 0;
  va_list args;            // указатель на аргументы
  va_start(args, format);  // выделение памяти для arg
  result = s21_parser(str, format, args);
  va_end(args);  // очищение памяти
  return result;
}

int s21_parser(char *str, const char *format, va_list args) {
  str[0] = '\0';
  int i = -1;
  int counter_symbols_str = 0;
  while (format[++i] != '\0') {
    if (format[i] != '%') {
      str[counter_symbols_str] = format[i];
      counter_symbols_str++;
    }
    if (format[i] == '%') {
      Prototype prot = {'\0', 0, 0, 0, 0, 0, 0, 0, -1, -1, '\0'};
      // обработка спецификатора и его параметров
      i = s21_read_format(&prot, format, i, args);
      if (prot.spec == '%') {
        str[counter_symbols_str] = format[i];
        counter_symbols_str++;
        continue;
      }
      // printf("prev sprintf - %s\n", str);
      counter_symbols_str =
          s21_args_to_str(counter_symbols_str, str, &prot, args);
      // printf("sprintf - %s\n", str);
    }
  }
  str[counter_symbols_str] = '\0';
  return counter_symbols_str;
}