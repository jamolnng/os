#include <stddef.h>
#include <stdlib.h>
#include <string.h>

size_t uitoa(unsigned int ui, char* str, unsigned int base) {
  char enc[36] = "0123456789abcdefghijklmnopqrstuvwxyz";
  size_t i = 0;
  do {
    str[i++] = enc[ui % base];
  } while (ui /= base);
  str[i] = '\0';
  strrev(str);
  return i;
}
