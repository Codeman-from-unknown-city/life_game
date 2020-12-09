#pragma once

#include <stdlib.h>
#include <stdio.h>

#define safe_free(ptr) __safe_free((void **) &(ptr))

FILE*
safe_fopen(const char* fname, const char* mode);
 
void*
safe_malloc(size_t size);

void
__safe_free(void** ptr);

