#include <stdlib.h>
#include <string.h>

size_t itoa(int i, char* str, unsigned int base) {
  if (i < 0) {
    str[0] = '-';
    return 1 + uitoa(-i, str + 1, base);
  }
  return uitoa(i, str, base);
}
