//
// Created by user on 25.11.2020.
//
#pragma once

#include "../bmp/bmp.h"

char**
create_initial_game_field(const unsigned char* buf, BITMAPINFOHEADER* info);

void
free_game_field(char** game_field);

char**
generate_next_gen(char** game_field, BITMAPINFOHEADER*);

void
pack(bmp_t* bmp, char** game_field);
