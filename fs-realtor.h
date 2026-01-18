#include "bit shenanigans.h"
#include "disk.h"
#include <stdio.h>

int gimme_a_free_block_in_and_mark_it(FILE *the_disk_file, uint8_t *bimap);

struct superBlock {
  char magic_no[8];
  uint32_t blockSize;
  uint32_t noOfBlocks;
  uint32_t blockPerGroup;
  uint32_t bitmap_location;
};
