//
// Created by user on 25.11.2020.
//
#include <Windows.h>
#include <stdbool.h>

#include "field.h"
#include "../utils/safe/safe.h"

static char**
create_2d_char_arr(int rows, int columns)
{
 char** arr_2d = safe_malloc(sizeof(char*) * rows);
 *arr_2d = safe_malloc(sizeof(char) * rows * columns);
 for (int i = 1; i < rows; i++)
   arr_2d[i] = arr_2d[i - 1] + columns;
 return arr_2d;
}

char**
create_initial_game_field(const unsigned char* buf, BITMAPINFOHEADER* info)
{
  char** game_field = create_2d_char_arr(info->biHeight, info->biWidth);
  int row = 0, col = 0;
  for (int i = 0; i < info->biSizeImage; i++)
    {
      if (col == info->biWidth)
        {
          row++;
          col = 0;
        }
      for (int j = 7; j >= 0; j--)
        game_field[row][col++] = !(buf[i] >> j & 0x01);
    }
  return game_field;
}

static int
calc_n_neighbors(char** game_field, int i, int j, int h, int w)
{
  bool is_not_bottom_edge = i != 0;
  bool is_not_top_edge = i != h - 1;
  bool is_not_left_edge = j != 0;
  bool is_not_right_edge = j != w - 1;
  int n_neighbors = 0;
  if (is_not_top_edge)
    {
      n_neighbors += game_field[i + 1][j];
      if (is_not_left_edge)
        n_neighbors += game_field[i + 1][j - 1];
      if (is_not_right_edge)
        n_neighbors += game_field[i + 1][j + 1];
    }
  if (is_not_bottom_edge)
    {
      n_neighbors += game_field[i - 1][j];
      if (is_not_left_edge)
        n_neighbors += game_field[i - 1][j - 1];
      if (is_not_right_edge)
        n_neighbors += game_field[i - 1][j + 1];
    }
  if (is_not_left_edge)
    n_neighbors += game_field[i][j - 1];
  if (is_not_right_edge)
    n_neighbors += game_field[i][j + 1];
  return n_neighbors;
}

char**
generate_next_gen(char** game_field, BITMAPINFOHEADER* info)
{
  char** next_gen = create_2d_char_arr(info->biHeight, info->biWidth);
  for (int i = 0; i < info->biHeight; i++)
      for (int j = 0; j < info->biWidth; j++)
        {
          int n_neighbors = calc_n_neighbors(game_field, i, j, info->biHeight, info->biWidth);
          next_gen[i][j] = game_field[i][j] == 1 ? n_neighbors >= 2 && n_neighbors <= 3 : n_neighbors == 3;
        }
  return next_gen;
}

void
free_game_field(char** game_field)
{
  safe_free((void**) &game_field);
  safe_free((void**) game_field);
}

void
pack(bmp_t* bmp, char** game_field)
{
  int k = -1;
  for (int i = 0; i < bmp->info_header.biHeight; i++)
    for (int j = 0; j < bmp->info_header.biWidth; j++)
      {
        int modulo_8 = j % 8;
        if (modulo_8 == 0)
          {
            k++;
            bmp->image[k] = 0;
          }
        if (game_field[i][j] == 0)
          bmp->image[k] |= 1 << (7 - modulo_8);
      }
}
