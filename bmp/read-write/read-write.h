#pragma once

#include <stdio.h>

typedef size_t (* read_write_fn)(void*, size_t, size_t, FILE*);

void
read_write_bmp_part(read_write_fn, void* buf, size_t size, FILE* stream, 
		    const char* err_msg);

