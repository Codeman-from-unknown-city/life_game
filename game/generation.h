#pragma once

#include "../bmp/bmp.h"

generation
get_first_gen(const unsigned char* buf, BITMAPINFOHEADER* info);

void
free_gen(generation gen);

generation
generate_next_gen(generation gen, BITMAPINFOHEADER*);

void
pack(bmp_t* bmp, generation gen);

