//
// Created by user on 25.11.2020.
//
#include <Windows.h>
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
read_bmp(FILE*);

void
write_bmp(FILE*, bmp_t*);
