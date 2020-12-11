#include <sys/stat.h>
#include <string.h>
#include "bmp/bmp.h"
#include "utils/safe/safe.h"
#include "utils/utils.h"
#include "game/generation.h"
#include "settings/settings.h"

#define DIR_PERMISSION 0777
#define MAX_NAME 256

int
main(int argc, char* argv[])
{
  settings_t settings = get_settings(argc, argv);
  mkdir(settings.output, DIR_PERMISSION);
  char output_path[MAX_NAME];
  uint64_t id = 0;
  char id_string[200];
  bmp_t bmp = read_bmp(settings.input);
  uint64_t max_iter_copy = settings.max_iter;
  uint64_t dump_freq_copy = settings.dump_freq;
  generation first_gen = get_first_gen(bmp.image, &bmp.info_header);
  generation next_gen;
  while (settings.max_iter != MAX_ITER_DEFAULT ? max_iter_copy-- : 1)
    {
      next_gen = generate_next_gen(first_gen, &bmp.info_header);
      if (--dump_freq_copy == 0)
        {
          pack(&bmp, next_gen);
          strcpy(output_path, settings.output);
          strcat(output_path, "/");
          itoa(id++, id_string);
          strcat(output_path, id_string);
          strcat(output_path, ".bmp");
          puts(output_path);
          write_bmp(output_path, &bmp);
          dump_freq_copy = settings.dump_freq;
        }
      free_gen(first_gen);
      first_gen = next_gen;
    }
  safe_free(bmp.image);
  return 0;
}
