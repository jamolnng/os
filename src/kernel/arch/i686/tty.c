#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <arch/i686/ports.h>
#include <arch/i686/vga.h>
#include <kernel/tty.h>

void terminal_putentryat_pos(unsigned char c, uint8_t color, size_t pos) {
  vga_buffer[pos] = vga_entry(c, color);
}

void terminal_putentryat_xy(unsigned char c, uint8_t color, size_t x,
                            size_t y) {
  terminal_putentryat_pos(c, color, y * VGA_WIDTH + x);
}

uint16_t terminal_getentryat_xy(size_t x, size_t y) {
  return vga_buffer[y * VGA_WIDTH + x];
}

void terminal_scroll() {
  for (int i, j = 1; j < VGA_HEIGHT; j++) {
    for (i = 0; i < VGA_WIDTH; i++) {
      vga_buffer[(j - 1) * VGA_WIDTH + i] = vga_buffer[j * VGA_WIDTH + i];
      if (j == VGA_HEIGHT - 1) {
        terminal_putentryat_xy(' ', 0x0F, i, j);
      }
    }
  }
  set_cursor_pos(VGA_WIDTH * (VGA_HEIGHT - 1));
}

void terminal_initialize(void) { terminal_clear(); }

void terminal_putchar(char c) {
  size_t cur = get_cursor_pos();
  switch (c) {
    case '\n':
      set_cursor_pos((cur / VGA_WIDTH + 1) * VGA_WIDTH);
      break;
    default:
      terminal_putentryat_pos(c, 0x0F, cur);
      set_cursor_pos(cur + 1);
      break;
  }
  cur = get_cursor_pos();
  if (cur >= VGA_WIDTH * VGA_HEIGHT) {
    terminal_scroll();
  }
}

void terminal_write(const char* data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    terminal_putchar(data[i]);
  }
}

void terminal_puts(const char* data) { terminal_write(data, strlen(data)); }

void terminal_clear() {
  for (size_t x, y = 0; y < VGA_HEIGHT; y++) {
    for (x = 0; x < VGA_WIDTH; x++) {
      terminal_putentryat_xy(' ', 0x0F, x, y);
    }
  }
  set_cursor_pos(0);
}

size_t get_cursor_pos() {
  port_out_b(VGA_CTRL_REG, 14);
  size_t pos = port_in_b(VGA_DATA_REG) << 8;
  port_out_b(VGA_CTRL_REG, 15);
  pos += port_in_b(VGA_DATA_REG);
  return pos;
}

void set_cursor_xy(size_t x, size_t y) { set_cursor_pos(y * VGA_WIDTH + x); }

void set_cursor_pos(size_t pos) {
  port_out_b(VGA_CTRL_REG, 14);
  port_out_b(VGA_DATA_REG, (unsigned char)(pos >> 8));
  port_out_b(VGA_CTRL_REG, 15);
  port_out_b(VGA_DATA_REG, (unsigned char)(pos & 0xFF));
}
