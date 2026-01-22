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

void mkfs(struct superBlock sb) {

  printf("reformatting fs");
  memcpy(sb.magic_no, "jaibheem", 8);
  sb.blockSize = BLOCK_SIZE;
  sb.blockPerGroup = 128;
  sb.noOfBlocks = BLOCK_COUNT;
  sb.bitmap_location = 1;

  char to_pad_buffer[BLOCK_SIZE];
  memset(to_pad_buffer, 0, BLOCK_SIZE);

  memcpy(to_pad_buffer, &sb, sizeof(sb));
  dwrite(the_disk_file, 0, to_pad_buffer);

  uint8_t bitmap_block[BLOCK_SIZE];
  memset(bitmap_block, 0, BLOCK_SIZE);
  bit_set_used(bitmap_block, 0);
  bit_set_used(bitmap_block, 1);
  dwrite(the_disk_file, 1, bitmap_block);
};
