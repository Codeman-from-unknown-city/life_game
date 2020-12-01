//
// Created by user on 25.11.2020.
//

#include <stdio.h>

#pragma once

void
read_write_bmp_part(size_t (* read_write_fn)(void*, size_t, size_t, FILE*),
                    void* buf, size_t size, FILE* stream, const char* err_msg);
