#include "bit shenanigans.h"

// bit shenanigans
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
