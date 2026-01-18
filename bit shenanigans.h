
#include <stdint.h>
#ifndef BIT_H

// bit shenanigans
void bit_set_used(uint8_t *bitmap, uint32_t BLOCK_NO);

void bit_set_free(uint8_t *bitmap, uint32_t BLOCK_NO);

int bit_status_chek(uint8_t *bitmap, uint32_t BLOCK_NO);

#endif // BIT_H
