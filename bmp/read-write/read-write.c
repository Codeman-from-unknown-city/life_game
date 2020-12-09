#include <stdlib.h>

#include "read-write.h"
#include "../../utils/log.h"

void
read_write_bmp_part(read_write_fn fn, void* buf, size_t size, FILE* stream, 
		    const char* err_msg)
{
  size_t n_read_or_write = (*fn)(buf, size, 1, stream);
  if (n_read_or_write != 1)
    {
      error_log("%s", err_msg);
      exit(1);
    }
}

