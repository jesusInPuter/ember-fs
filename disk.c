#include "disk.h"

// writer an reader
void dread(FILE *disk, int BLOCK_NO, void *buff) {
  fseek(disk, BLOCK_NO * BLOCK_SIZE, SEEK_SET);
  fread(buff, BLOCK_SIZE, 1, disk);
}

void dwrite(FILE *disk, int BLOCK_NO, const void *buff) {
  fseek(disk, BLOCK_NO * BLOCK_SIZE, SEEK_SET);
  fwrite(buff, BLOCK_SIZE, 1, disk);
  fflush(disk);
};
