#pragma once

#include <stddef.h>
#include <sys/cdefs.h>

#ifndef NULL
#define NULL (void*)0
#endif

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__)) void abort(void);

size_t itoa(int i, char* str, unsigned int base);
size_t uitoa(unsigned int ui, char* str, unsigned int base);

#ifdef __cplusplus
}
#endif
