#include "safe.h"
#include "../log.h"

FILE*
safe_fopen(const char* fname, const char* mode)
{
  FILE* f = fopen(fname, mode);
  if (f == NULL)
    {
      error_log("can't open %s file", fname);
      exit(1);
    }
  return f;
}

void*
safe_malloc(size_t size)
{
  void* buff = malloc(size);
  if (buff == NULL)
    {
      error_log("can't allocate memory");
      exit(1);
    }
  return buff;
}

void
__safe_free(void** ptr)
{
  if (ptr == NULL)
    return;
  free(*ptr);
  *ptr = NULL;
}

