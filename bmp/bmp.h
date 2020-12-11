#include <../utils/winapi.h>
#include <stdio.h>
#include <stdint.h>

#pragma once

typedef struct {
    BITMAPINFOHEADER info_header;
    BITMAPFILEHEADER fheader;
    uint64_t color_palette;
    unsigned char* image;
} bmp_t;

bmp_t
read_bmp(const char* bmp_file_name);

void
write_bmp(const char* output_file_name, bmp_t*);

