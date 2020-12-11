#pragma once

#include <stdint.h>

#define MAX_ITER_DEFAULT 0
#define DUMP_FREQ_DEFAULT 0

typedef struct 
{
  uint64_t max_iter;
  uint64_t dump_freq;
  char* input;
  char* output;
} settings_t;

settings_t
get_settings(int argc, char* argv[]);

