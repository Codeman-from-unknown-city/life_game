#include <stdio.h>

#include "bmp/bmp.h"
#include "utils/safe/safe.h"
#include "game/field.h"

int
main(int argc, char* argv[])
{
  FILE* bmp_f = safe_fopen("temp.bmp", "rb");
  bmp_t bmp = read_bmp(bmp_f);
  char** game_field = create_initial_game_field(bmp.image, &bmp.info_header);
  char** next_gen = generate_next_gen(game_field, &bmp.info_header);
  free_game_field(game_field);
  pack(&bmp, next_gen);
  FILE* a = safe_fopen("temp.bmp", "wb");
  write_bmp(a, &bmp);
  return 0;
}

