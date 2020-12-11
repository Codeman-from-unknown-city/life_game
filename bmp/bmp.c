#include <stdio.h>
#include "bmp.h"
#include "read-write/read-write.h"
#include "../utils/safe/safe.h"

#define SIZE_OF_COLOR_PALETTE 8

bmp_t
read_bmp(const char* bmp_file_name)
{
  FILE* bmp_f = safe_fopen(bmp_file_name, "rb");
  bmp_t bmp;
  read_write_bmp_part(fread, &bmp.fheader, sizeof(BITMAPFILEHEADER), bmp_f, 
		      "can't read bitmap file header");
  read_write_bmp_part(fread, &bmp.info_header, sizeof(BITMAPINFOHEADER), bmp_f, 
		      "can't read bitmap info header");
  read_write_bmp_part(fread, &bmp.color_palette, SIZE_OF_COLOR_PALETTE, bmp_f, 
		      "can't read bitmap color palette");
  fseek(bmp_f, bmp.fheader.bfOffBits, SEEK_SET);
  bmp.image = safe_malloc(bmp.info_header.biSizeImage);
  read_write_bmp_part(fread, bmp.image, bmp.info_header.biSizeImage, bmp_f, 
		      "can't read image");
  fclose(bmp_f);
  return bmp;
}

void
write_bmp(const char* output_file_name, bmp_t* bmp)
{
  FILE* f = safe_fopen(output_file_name, "wb");
  read_write_bmp_part((read_write_fn) fwrite, &bmp->fheader, sizeof(BITMAPFILEHEADER), f, 
		      "can't write bitmap file header");
  read_write_bmp_part((read_write_fn) fwrite,
                      &bmp->info_header, sizeof(BITMAPINFOHEADER), f, 
		      "can't write bitmap info");
  read_write_bmp_part((read_write_fn) fwrite, &bmp->color_palette, SIZE_OF_COLOR_PALETTE, f,
		      "can't write bitmap color palette");
  fseek(f, bmp->fheader.bfOffBits, SEEK_SET);
  read_write_bmp_part((read_write_fn) fwrite, bmp->image, bmp->info_header.biSizeImage, f, 
		      "can't write image");
  fclose(f);
}

