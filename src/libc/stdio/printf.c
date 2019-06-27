#include <stdarg.h>
#include <stdio.h>

int printf(const char* fmt, ...) {
  va_list arg;
  int done;
  va_start(arg, fmt);
  done = vprintf(fmt, arg);
  va_end(arg);
  return done;
}
