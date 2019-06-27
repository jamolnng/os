#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <kernel/tty.h>

static bool print(const char* data, size_t length) {
  const unsigned char* bytes = (const unsigned char*)data;
  for (size_t i = 0; i < length; i++) {
    if (putchar(bytes[i]) == EOF) {
      return false;
    }
  }
  return true;
}

int vprintf(const char* format, va_list arg) {
  int written = 0;
  unsigned int base = 10;
  bool is_signed = true;
  bool is_upper = false;
  int i;
  char toa[12];
  size_t len;
  char c;
  const char* cc;
  while (*format != '\0') {
    size_t max_rem = INT_MAX - written;
    if (*format == '%') {
      switch (*(++format)) {
        case 'c':
          c = (char)va_arg(arg, int /* char promotes to int */);
          if (!max_rem) {
            // TODO: Set errno to EOVERFLOW.
            return -1;
          }
          if (!print(&c, sizeof(c))) {
            return -1;
          }
          written++;
          break;
        case 's':
          cc = va_arg(arg, const char*);
          len = strlen(cc);
          if (max_rem < len) {
            // TODO: Set errno to EOVERFLOW.
            return -1;
          }
          if (!print(cc, len)) {
            return -1;
          }
          written += len;
          break;
        case 'i':
        case 'd':
          is_signed = true;
          base = 10;
          goto print_n;
        case 'u':
          is_signed = false;
          base = 10;
          goto print_n;
        case 'o':
          is_signed = false;
          base = 8;
          goto print_n;
        case 'x':
          is_signed = false;
          base = 16;
          is_upper = false;
          goto print_n;
        case 'X':
          is_signed = false;
          base = 16;
          is_upper = true;
          goto print_n;
        case 'b':
          is_signed = false;
          base = 2;
        print_n:
          i = va_arg(arg, int);
          if (is_signed) {
            itoa(i, toa, base);
          } else {
            uitoa(i, toa, base);
          }
          len = strlen(toa);
          if (max_rem < len) {
            // TODO: Set errno to EOVERFLOW.
            return -1;
          }
          if (is_upper) {
            i = 0;
            while (toa[i]) {
              toa[i] = toupper(toa[i]);
              i++;
            }
          }
          if (!print(toa, len)) {
            return -1;
          }
          written += len;
          break;
      }
    } else {
      putchar(*format);
      written++;
    }
    format++;
  }
  return written;
}
