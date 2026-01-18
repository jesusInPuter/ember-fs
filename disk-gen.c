#include "bit shenanigans.h"
#include "disk.h"
#include "fs-realtor.h"
#include <string.h>

int main() {

  FILE *the_disk_file;
  the_disk_file = fopen("disk.img", "w+b");

  if (!the_disk_file) {
    perror("file didnt open");
    return 1;
  }

  struct superBlock sb;
  memcpy(sb.magic_no, "jaibheem", 8);
  sb.blockSize = BLOCK_SIZE;
  sb.blockPerGroup = 128;
  sb.noOfBlocks = BLOCK_COUNT;
  sb.bitmap_location = 1;

  char to_pad_buffer[BLOCK_SIZE];

  memset(to_pad_buffer, 0, BLOCK_SIZE);
  memcpy(to_pad_buffer, &sb, sizeof(sb));
  dwrite(the_disk_file, 0, to_pad_buffer);

  struct superBlock sb_viewer;
  char read_buffer[BLOCK_SIZE];

  dread(the_disk_file, 0, read_buffer);
  memcpy(&sb_viewer, read_buffer, sizeof(sb_viewer));

  if (memcmp(sb.magic_no, sb_viewer.magic_no, sizeof(sb.magic_no)) != 0) {
    printf("hell naaaaaa!\n");
    return 1;
  }

  uint8_t bitmap_block[BLOCK_SIZE];
  memset(bitmap_block, 0, BLOCK_SIZE);

  int bitmap = 0;

  bit_set_used(bitmap_block, 0);
  bit_set_used(bitmap_block, 1);

  dwrite(the_disk_file, 1, bitmap_block);

  fclose(the_disk_file);
  return 0;
}
