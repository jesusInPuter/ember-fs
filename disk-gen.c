#include <stdint.h>
#include <stdio.h>

#define DISK_SIZE (1024 * 1024)

int main() {
  FILE *the_disk_file;
  the_disk_file = fopen("disk.img", "wb");

  if (!the_disk_file) {
    perror("file didnt open");
    return 1;
  }

  char nill = 0;

  for (int i = 0; i < DISK_SIZE; i++) {
    fwrite(&nill, 1, 1, the_disk_file);
  }

  fclose(the_disk_file);

  return 0;
}
