#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  char *res = S21_NULL;
  if (str) {
    s21_size_t length = s21_strlen(str);
    res = (char *)malloc(length + 1);
    for (s21_size_t i = 0; i < length; i++) {
      if (str[i] > 96 && str[i] < 123) {
        res[i] = str[i] - 32;
      } else {
        res[i] = str[i];
      }
    }
    res[length] = '\0';
  }

  return res;
}

void *s21_to_lower(const char *str) {
  char *res = S21_NULL;
  if (str) {
    s21_size_t length = s21_strlen(str);
    res = (char *)malloc(length + 1);
    for (s21_size_t i = 0; i < length; i++) {
      if (str[i] > 64 && str[i] < 91) {
        res[i] = str[i] + 32;
      } else {
        res[i] = str[i];
      }
    }
    res[length] = '\0';
  }

  return res;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = S21_NULL;
  if (src != S21_NULL && str != S21_NULL) {
    s21_size_t lenSrc = s21_strlen(src);
    s21_size_t lenStr = s21_strlen(str);
    if (start_index <= lenSrc) {
      res = (char *)malloc(lenSrc + lenStr + 1);
      if (lenStr == 0) {
        s21_strcpy(res, src);
      } else {
        s21_strncpy(res, src, start_index);
        for (s21_size_t i = 0; i < lenStr; i++) {
          res[start_index + i] = str[i];
        }
        for (s21_size_t i = start_index; i < lenSrc; i++) {
          res[i + lenStr] = src[i];
        }
        res[lenSrc + lenStr] = '\0';
      }
    }
  }

  return res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = S21_NULL;
  if (src) {
    int lenString = s21_strlen(src);
    int flag = 1;
    int lenFinish = 0;
    if (trim_chars == S21_NULL || s21_strlen(trim_chars) == 0) {
      trim_chars = "\n\t ";
    }
    int lenChars = s21_strlen(trim_chars);
    int indStart = s21_strspn(src, trim_chars);
    for (int i = lenString - 1; i > indStart; i--) {
      flag = 0;
      for (int j = 0; j < lenChars; j++) {
        if (src[i] == trim_chars[j]) {
          flag = 1;
          lenFinish = lenFinish + 1;
        }
      }
      if (flag == 0) {
        i = indStart;
      }
    }
    if (indStart == 0 && lenFinish == 0) {
      res = (char *)malloc(lenString + 1);
      s21_strcpy(res, src);
    } else {
      int length = lenString - indStart - lenFinish;
      res = (char *)malloc(length + 1);
      for (int i = 0; i < length; i++) {
        res[i] = src[i + indStart];
      }
      res[length] = '\0';
    }
  }
  return res;
}