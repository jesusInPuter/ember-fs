#ifndef DISK_H
#define DISK_H

#include <stdint.h>
#include <stdio.h>

#define DISK_SIZE (1024 * 1024)
#define BLOCK_SIZE 4096
#define BLOCK_COUNT (DISK_SIZE / BLOCK_SIZE)

void dread(FILE *disk, int block_no, void *buf);
void dwrite(FILE *disk, int block_no, const void *buf);

#endif
