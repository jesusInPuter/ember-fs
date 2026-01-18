#include "fs-realtor.h"

int gimme_a_free_block_in_and_mark_it(FILE *the_disk_file, uint8_t *bimap) {
  for (int i = 0 + 2; i < BLOCK_COUNT; i++) {
    if (!bit_status_chek(bimap, i)) {
      bit_set_used(bimap, i);          // update teh map
      dwrite(the_disk_file, 1, bimap); // write it on disk block 1
      return i;
    }
  }
  return -1;
}

struct superBlock {
  char magic_no[8];
  uint32_t blockSize;
  uint32_t noOfBlocks;
  uint32_t blockPerGroup;
  uint32_t bitmap_location;
};
