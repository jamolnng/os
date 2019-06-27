#pragma once

#include <stddef.h>
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif
int strlen(const char*);
char* strrev(char*);
int strcmp(const char*, const char*);
int memcmp(const void*, const void*, size_t);
void* memcpy(void*, const void*, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);

#ifdef __cplusplus
}
#endif
