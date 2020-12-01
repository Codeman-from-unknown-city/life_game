//
// Created by sergei on 24.11.2020.
//
#include <stdlib.h>
#include <stdio.h>

#pragma once

FILE*
safe_fopen(const char* fname, const char* mode);
 
void*
safe_malloc(size_t size);

void
safe_free(void** ptr);
