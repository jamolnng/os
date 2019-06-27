#pragma once

#include <stdint.h>

#define VGA_BUFFER_START_ADDR 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_CTRL_REG 0x3D4
#define VGA_DATA_REG 0x3D5

static uint16_t* const vga_buffer = (uint16_t* const)VGA_BUFFER_START_ADDR;

typedef enum {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15,
} vga_color;

static inline uint8_t vga_entry_color(vga_color fg, vga_color bg) {
  return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
  return (uint16_t)uc | (uint16_t)color << 8;
}
