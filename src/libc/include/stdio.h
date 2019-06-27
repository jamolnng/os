#pragma once
#include <stdarg.h>
#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int vprintf(const char*, va_list);

int printf(const char*, ...);
int putchar(int);
int puts(const char*);

#ifdef __cplusplus
}
#endif
