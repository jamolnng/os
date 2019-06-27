#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <cpu/isr.h>
#include <kernel/tty.h>

extern "C" void kernel_init(void) { terminal_initialize(); }

extern "C" void kernel_main(void) {
  printf("Hello, kernel World!\n");
  for (int i = 10; i < 32; i++) {
    printf("%x ", i);
  }
  puts("");
  printf("%i %d %u 0o%o 0x%x 0x%X 0b%b\n", -20, 20, 20, 20, 0xff, 0xff, 20);
  //__asm__ __volatile__("int $2");
  //__asm__ __volatile__("int $3");
  for (int i = 0; i < 500; i++) {
    printf("%d\n", i);
    for (int j = 0; j < INT32_MAX / 33; j++) {
    }
  }
}
