#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *buff = (char *)str;
  char *res = S21_NULL;
  for (; n && buff; n--) {
    if (*buff == (char)c) {
      res = buff;
      n = 1;
    }
    buff++;
  }
  return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0, i = -1;
  unsigned char *arr1 = (unsigned char *)str1;
  unsigned char *arr2 = (unsigned char *)str2;
  if (n) do {
      i++;
      res = (int)arr1[i] - (int)arr2[i];
      n--;
    } while (n && (int)arr1[i] == (int)arr2[i]);
  return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *arr1 = (unsigned char *)dest;
  unsigned char *arr2 = (unsigned char *)src;
  while (n) {
    *arr1 = *arr2;
    arr1++;
    arr2++;
    n--;
  }
  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  unsigned char *arr1 = (unsigned char *)dest;
  unsigned char *arr2 = (unsigned char *)src;
  if (dest > src) {
    while (n--) {
      arr1[n] = arr2[n];
    }
  } else if (dest < src) {
    while (n--) {
      *arr1++ = *arr2++;
    }
  }
  return arr1;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *arr = (unsigned char *)str;
  while (n) {
    *arr = c;
    arr++;
    n--;
  }
  return str;
}

char *s21_strcat(char *dest, const char *src) {
  char *res = dest;
  for (; *dest != '\0'; dest++) {
  }
  while (*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }
  return res;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *res = dest;
  for (; *dest != '\0'; dest++) {
  }
  while (*src != '\0' && n) {
    *dest = *src;
    dest++;
    src++;
    n--;
  }
  return res;
}

char *s21_strchr(const char *str, int c) {
  char *res = *str == c ? (char *)str : S21_NULL;
  char *buff = (char *)str;
  while (*buff != c && *buff != '\0') {
    buff++;
    if (*buff == c) {
      res = buff;
    }
  }
  return res;
}

int s21_strcmp(const char *str1, const char *str2) {
  int res = *str1 == *str2 ? 0 : *str1 - *str2;
  while (*str1 == *str2 && *str1) {
    str1++;
    str2++;
    res = *str1 - *str2;
  }
  return res;
}

// int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
//   int res = (*str1 != *str2) && n ? *str1 - *str2 : 0;
//   while (*str1 == *str2 && *str1 && n) {
//     str1++;
//     str2++;
//     res = *str1 - *str2;
//     n--;
//   }
//   return res;
// }

// fix
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = (*str1 != *str2) && n ? *str1 - *str2 : 0;
  n--;
  while (*str1 == *str2 && *str1 && n) {
    str1++;
    str2++;
    res = *str1 - *str2;
    n--;
  }
  return res;
}

char *s21_strcpy(char *dest, const char *src) {
  s21_size_t i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  while (src[i] != '\0' && n) {
    dest[i] = src[i];
    i++;
    n--;
  }
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  short check = 1;
  for (; check && *str1 != '\0'; str1++) {
    for (int i = 0; check && str2[i] != '\0'; i++) {
      if (*str1 == str2[i]) check = 0;
    }
    count += check ? 1 : 0;
  }
  return count;
}

char *s21_strerror(int errnum) {
  char *res = S21_NULL;
  static char buf[128] = {'\0'};
#if defined(__APPLE__)
#define ERRMAX 107
#define ERRMIN 0

  const char *error[] = {"Undefined error: 0",
                         "Operation not permitted",
                         "No such file or directory",
                         "No such process",
                         "Interrupted system call",
                         "Input/output error",
                         "Device not configured",
                         "Argument list too long",
                         "Exec format error",
                         "Bad file descriptor",
                         "No child processes",
                         "Resource deadlock avoided",
                         "Cannot allocate memory",
                         "Permission denied",
                         "Bad address",
                         "Block device required",
                         "Resource busy",
                         "File exists",
                         "Cross-device link",
                         "Operation not supported by device",
                         "Not a directory",
                         "Is a directory",
                         "Invalid argument",
                         "Too many open files in system",
                         "Too many open files",
                         "Inappropriate ioctl for device",
                         "Text file busy",
                         "File too large",
                         "No space left on device",
                         "Illegal seek",
                         "Read-only file system",
                         "Too many links",
                         "Broken pipe",
                         "Numerical argument out of domain",
                         "Result too large",
                         "Resource temporarily unavailable",
                         "Operation now in progress",
                         "Operation already in progress",
                         "Socket operation on non-socket",
                         "Destination address required",
                         "Message too long",
                         "Protocol wrong type for socket",
                         "Protocol not available",
                         "Protocol not supported",
                         "Socket type not supported",
                         "Operation not supported",
                         "Protocol family not supported",
                         "Address family not supported by protocol family",
                         "Address already in use",
                         "Can't assign requested address",
                         "Network is down",
                         "Network is unreachable",
                         "Network dropped connection on reset",
                         "Software caused connection abort",
                         "Connection reset by peer",
                         "No buffer space available",
                         "Socket is already connected",
                         "Socket is not connected",
                         "Can't send after socket shutdown",
                         "Too many references: can't splice",
                         "Operation timed out",
                         "Connection refused",
                         "Too many levels of symbolic links",
                         "File name too long",
                         "Host is down",
                         "No route to host",
                         "Directory not empty",
                         "Too many processes",
                         "Too many users",
                         "Disc quota exceeded",
                         "Stale NFS file handle",
                         "Too many levels of remote in path",
                         "RPC struct is bad",
                         "RPC version wrong",
                         "RPC prog. not avail",
                         "Program version wrong",
                         "Bad procedure for program",
                         "No locks available",
                         "Function not implemented",
                         "Inappropriate file type or format",
                         "Authentication error",
                         "Need authenticator",
                         "Device power is off",
                         "Device error",
                         "Value too large to be stored in data type",
                         "Bad executable (or shared library)",
                         "Bad CPU type in executable",
                         "Shared library version mismatch",
                         "Malformed Mach-o file",
                         "Operation canceled",
                         "Identifier removed",
                         "No message of desired type",
                         "Illegal byte sequence",
                         "Attribute not found",
                         "Bad message",
                         "EMULTIHOP (Reserved)",
                         "No message available on STREAM",
                         "ENOLINK (Reserved)",
                         "No STREAM resources",
                         "Not a STREAM",
                         "Protocol error",
                         "STREAM ioctl timeout",
                         "Operation not supported on socket",
                         "Policy not found",
                         "State not recoverable",
                         "Previous owner died",
                         "Interface output queue is full"};
  if (errnum >= ERRMAX || errnum < ERRMIN) {
    s21_sprintf(buf, "Unknown error: %d", errnum);
    res = buf;
  } else {
    res = (char *)error[errnum];
  }
#elif defined(__linux__)
#define ERRMAX 134
#define ERRMIN 0

  static const char *error[] = {
      "Success",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "No such device or address",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource temporarily unavailable",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Device or resource busy",
      "File exists",
      "Invalid cross-device link",
      "No such device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Numerical result out of range",
      "Resource deadlock avoided",
      "File name too long",
      "No locks available",
      "Function not implemented",
      "Directory not empty",
      "Too many levels of symbolic links",
      "Unknown error 41",
      "No message of desired type",
      "Identifier removed",
      "Channel number out of range",
      "Level 2 not synchronized",
      "Level 3 halted",
      "Level 3 reset",
      "Link number out of range",
      "Protocol driver not attached",
      "No CSI structure available",
      "Level 2 halted",
      "Invalid exchange",
      "Invalid request descriptor",
      "Exchange full",
      "No anode",
      "Invalid request code",
      "Invalid slot",
      "Unknown error 58",
      "Bad font file format",
      "Device not a stream",
      "No data available",
      "Timer expired",
      "Out of streams resources",
      "Machine is not on the network",
      "Package not installed",
      "Object is remote",
      "Link has been severed",
      "Advertise error",
      "Srmount error",
      "Communication error on send",
      "Protocol error",
      "Multihop attempted",
      "RFS specific error",
      "Bad message",
      "Value too large for defined data type",
      "Name not unique on network",
      "File descriptor in bad state",
      "Remote address changed",
      "Can not access a needed shared library",
      "Accessing a corrupted shared library",
      ".lib section in a.out corrupted",
      "Attempting to link in too many shared libraries",
      "Cannot exec a shared library directly",
      "Invalid or incomplete multibyte or wide character",
      "Interrupted system call should be restarted",
      "Streams pipe error",
      "Too many users",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol",
      "Address already in use",
      "Cannot assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Transport endpoint is already connected",
      "Transport endpoint is not connected",
      "Cannot send after transport endpoint shutdown",
      "Too many references: cannot splice",
      "Connection timed out",
      "Connection refused",
      "Host is down",
      "No route to host",
      "Operation already in progress",
      "Operation now in progress",
      "Stale file handle",
      "Structure needs cleaning",
      "Not a XENIX named type file",
      "No XENIX semaphores available",
      "Is a named type file",
      "Remote I/O error",
      "Disk quota exceeded",
      "No medium found",
      "Wrong medium type",
      "Operation canceled",
      "Required key not available",
      "Key has expired",
      "Key has been revoked",
      "Key was rejected by service",
      "Owner died",
      "State not recoverable",
      "Operation not possible due to RF-kill",
      "Memory page has hardware error"};
  if (errnum >= ERRMAX || errnum < ERRMIN) {
    s21_sprintf(buf, "Unknown error %d", errnum);
    res = buf;
  } else {
    res = (char *)error[errnum];
  }
#endif
  return res;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t count = 0;
  if (str)
    while (*str++) {
      count++;
    }
  return count;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = S21_NULL;
  short check = 1;
  for (; check && *str1 != '\0'; str1++) {
    for (int i = 0; check && str2[i] != '\0'; i++) {
      if (*str1 == str2[i]) check = 0;
    }
    if (!check) res = (char *)str1;
  }
  return res;
}

char *s21_strrchr(const char *str, int c) {
  char *res = *str == c ? (char *)str : S21_NULL;
  while (*str != '\0') {
    str++;
    if (*str == c) res = (char *)str;
  }
  return res;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  short check = 1;
  for (; check && *str1 != '\0'; str1++) {
    check = 0;
    for (int i = 0; str2[i] != '\0'; i++) {
      if (*str1 == str2[i]) {
        check = 1;
      }
    }
    count += check;
  }
  return count;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *res = *needle ? S21_NULL : (char *)haystack;
  short check = 0;
  while (*haystack && !check) {
    if (haystack[0] == needle[0]) {
      res = (char *)haystack;
      check = 1;
      for (int i = 1, j = 1; check && needle[i] != '\0'; i++, j++) {
        check = haystack[j] == needle[i] ? 1 : 0;
      }
      if (!check) res = S21_NULL;
    }
    haystack++;
  }
  return res;
}

char *mystrchr(const char *s, const char c) {
  while (*s && *s != c) ++s;
  return (*s) ? (char *)s : NULL;
}

char *s21_strtok(char *str, const char *delim) {
  static char *next;

  if (str) {
    next = str;
    while (*next && mystrchr(delim, *next)) *next++ = '\0';
  }

  if (!*next) return NULL;

  str = next;

  while (*next && !mystrchr(delim, *next)) ++next;
  while (*next && mystrchr(delim, *next)) *next++ = '\0';

  return str;
}
