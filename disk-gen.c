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

int main() {

  FILE *the_disk_file;
  the_disk_file = fopen("disk.img", "w+b");

  if (!the_disk_file) {
    perror("file didnt open");
    return 1;
  }

  char *A = malloc(BLOCK_SIZE);
  char *B = malloc(BLOCK_SIZE);

  memset(A, 'f', BLOCK_SIZE);
  memset(B, 'a', BLOCK_SIZE);

  for (int i = 0; i < BLOCK_COUNT; i++) {
    if (i % 2 == 0) {
      dwrite(the_disk_file, i, A);
    } else {
      dwrite(the_disk_file, i, B);
    }
  }

  free(A);
  free(B);

  fclose(the_disk_file);

  return 0;
}
