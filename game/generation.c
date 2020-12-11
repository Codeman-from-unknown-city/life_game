#include <../utils/winapi.h>
#include <stdbool.h>
#include "generation.h"
#include "../utils/safe/safe.h"

typedef char** generation;

static char**
create_2d_char_arr(int rows, int columns)
{
 char** arr_2d = safe_malloc(sizeof(char*) * rows);
 *arr_2d = safe_malloc(sizeof(char) * rows * columns);
 for (int i = 1; i < rows; i++)
   arr_2d[i] = arr_2d[i - 1] + columns;
 return arr_2d;
}

generation
get_first_gen(const unsigned char* buf, BITMAPINFOHEADER* info)
{
  generation first_gen = create_2d_char_arr(info->biHeight, info->biWidth);
  int row = 0, col = 0;
  for (int i = 0; i < info->biSizeImage; i++)
    {
      if (col == info->biWidth)
        {
          row++;
          col = 0;
        }
      for (int j = 7; j >= 0; j--)
        first_gen[row][col++] = !(buf[i] >> j & 0x01);
    }
  return first_gen;
}

static int
calc_n_neighbors(generation gen, int i, int j, int h, int w)
{
  bool is_not_bottom_edge = i != 0;
  bool is_not_top_edge = i != h - 1;
  bool is_not_left_edge = j != 0;
  bool is_not_right_edge = j != w - 1;
  int n_neighbors = 0;
  if (is_not_top_edge)
    {
      n_neighbors += gen[i + 1][j];
      if (is_not_left_edge)
        n_neighbors += gen[i + 1][j - 1];
      if (is_not_right_edge)
        n_neighbors += gen[i + 1][j + 1];
    }
  if (is_not_bottom_edge)
    {
      n_neighbors += gen[i - 1][j];
      if (is_not_left_edge)
        n_neighbors += gen[i - 1][j - 1];
      if (is_not_right_edge)
        n_neighbors += gen[i - 1][j + 1];
    }
  if (is_not_left_edge)
    n_neighbors += gen[i][j - 1];
  if (is_not_right_edge)
    n_neighbors += gen[i][j + 1];
  return n_neighbors;
}

generation
generate_next_gen(generation gen, BITMAPINFOHEADER* info)
{
  generation next_gen = create_2d_char_arr(info->biHeight, info->biWidth);
  for (int i = 0; i < info->biHeight; i++)
      for (int j = 0; j < info->biWidth; j++)
        {
          int n_neighbors = calc_n_neighbors(gen, i, j, info->biHeight, info->biWidth);
          next_gen[i][j] = gen[i][j] == 1 ? n_neighbors >= 2 && n_neighbors <= 3 : n_neighbors == 3;
        }
  return next_gen;
}

void
free_gen(generation gen)
{
  safe_free(*gen);
  safe_free(gen);
}

void
pack(bmp_t* bmp, generation gen)
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
        if (gen[i][j] == 0)
          bmp->image[k] |= 1 << (7 - modulo_8);
      }
}

