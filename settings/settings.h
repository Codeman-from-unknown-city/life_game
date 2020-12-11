#pragma once

#include <stdint.h>

typedef struct 
{
  uint64_t max_iter;
  uint64_t dump_freq;
  char* input;
  char* output;
} settings;

settings
get_settings(int argc, char* argv[]);

