#pragma once

#include <stdint.h>

typedef struct 
{
  uint64 max_iter;
  uint64 dunp_freq;
  char* input;
  char* output;
} settings;

settings
get_settings(int argc, char* argv[]);

