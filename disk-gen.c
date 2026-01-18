#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISK_SIZE (1024 * 1024)
#define BLOCK_SIZE 4096
#define BLOCK_COUNT (DISK_SIZE / BLOCK_SIZE)

void dread(FILE *disk, int BLOCK_NO, void *buff) {
  fseek(disk, BLOCK_NO * BLOCK_SIZE, SEEK_SET);
  fread(buff, BLOCK_SIZE, 1, disk);
}

void dwrite(FILE *disk, int BLOCK_NO, const void *buff) {
  fseek(disk, BLOCK_NO * BLOCK_SIZE, SEEK_SET);
  fwrite(buff, BLOCK_SIZE, 1, disk);
  fflush(disk);
};

void bit_set_used(uint8_t *bitmap, uint32_t BLOCK_NO) {
  int byte_no = BLOCK_NO / 8;
  int bit_no = BLOCK_NO % 8;
  bitmap[byte_no] |= (1 << bit_no);
};

void bit_set_free(uint8_t *bitmap, uint32_t BLOCK_NO) {
  int byte_no = BLOCK_NO / 8;
  int bit_no = BLOCK_NO % 8;
  bitmap[byte_no] &= ~(1 << bit_no);
}

int bit_status_chek(uint8_t *bitmap, uint32_t BLOCK_NO) {
  int byte_no = BLOCK_NO / 8;
  int bit_no = BLOCK_NO % 8;
  return ((bitmap[byte_no] >> bit_no) & 1);
}

struct superBlock {
  char magic_no[8];
  uint32_t blockSize;
  uint32_t noOfBlocks;
  uint32_t blockPerGroup;
};

int main() {

  FILE *the_disk_file;
  the_disk_file = fopen("disk.img", "w+b");

  if (!the_disk_file) {
    perror("file didnt open");
    return 1;
  }

  // char *A = malloc(BLOCK_SIZE);
  // char *B = malloc(BLOCK_SIZE);
  //
  // memset(A, 'f', BLOCK_SIZE);
  // memset(B, 'a', BLOCK_SIZE);
  //
  // for (int i = 0; i < BLOCK_COUNT; i++) {
  //   if (i % 2 == 0) {
  //     dwrite(the_disk_file, i, A);
  //   } else {
  //     dwrite(the_disk_file, i, B);
  //   }
  // }
  //
  // free(A);
  // free(B);
  //

  struct superBlock sb;
  sb.blockSize = BLOCK_SIZE;
  sb.blockPerGroup = 128;
  sb.noOfBlocks = BLOCK_COUNT;

  memcpy(sb.magic_no, "jaibheem", 8);
  char padded_buffer[BLOCK_SIZE];

  memset(padded_buffer, 0, BLOCK_SIZE);
  memcpy(padded_buffer, &sb, sizeof(sb));
  dwrite(the_disk_file, 0, padded_buffer);

  struct superBlock sb_viewer;
  char read_buffer[BLOCK_SIZE];

  dread(the_disk_file, 0, read_buffer);
  memcpy(&sb_viewer, read_buffer, sizeof(sb_viewer));
  fclose(the_disk_file);

  if (memcmp(sb.magic_no, sb_viewer.magic_no, sizeof(sb.magic_no)) != 0) {
    printf("hell naaaaaa!\n");
    return 1;
  }

  uint8_t bitmap_block[BLOCK_SIZE];
  memset(bitmap_block, 0, BLOCK_SIZE);

  int bitmap = 0;

  return 0;
}
