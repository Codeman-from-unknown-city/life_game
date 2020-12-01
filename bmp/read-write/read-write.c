//
// Created by user on 25.11.2020.
//
#include <stdlib.h>

#include "read-write.h"
#include "../../utils/log.h"

void
read_write_bmp_part(size_t (* read_write_fn)(void*, size_t, size_t, FILE*),
                    void* buf, size_t size, FILE* stream, const char* err_msg)
{
  size_t n_read_or_write = (* read_write_fn)(buf, size, 1, stream);
  if (n_read_or_write != 1)
    {
      error_log("%s", err_msg);
      exit(1);
    }
}
