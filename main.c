#include "bit shenanigans.h"
#include "disk.h"
#include "fs-realtor.h"
#include <stdio.h>
#include <string.h>

int main() {

  FILE *the_disk_file;
  the_disk_file = fopen("disk.img", "r+b");
  if (!the_disk_file) {
    printf("file system was not found in src dir\n");
    the_disk_file = fopen("disk.img", "w+b");
  }

  char sb_buff[BLOCK_SIZE];
  dread(the_disk_file, 0, sb_buff);

  struct superBlock sb;
  memcpy(&sb, sb_buff, sizeof(sb));

  int yes_magic = (memcmp(&sb.magic_no, "jaibheem", 8) == 0);

  if (!yes_magic) {
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
  }

  uint8_t bitmap_block[BLOCK_SIZE];
  dread(the_disk_file, sb.bitmap_location, bitmap_block);
  int block_yes =
      gimme_a_free_block_in_and_mark_it(the_disk_file, bitmap_block);
  printf("alocated block : %d\n", block_yes);

  fclose(the_disk_file);
  return 0;
}
