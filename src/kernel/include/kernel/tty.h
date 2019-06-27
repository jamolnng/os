#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_puts(const char* data);
void terminal_clear();

size_t get_cursor_pos();
void set_cursor_xy(size_t x, size_t y);
void set_cursor_pos(size_t pos);

#ifdef __cplusplus
}
#endif
