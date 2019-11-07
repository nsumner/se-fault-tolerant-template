
#include<inttypes.h>
#include<stdlib.h>

uint8_t bytes[5] = {9, 11, 13, 17, 19};

uint8_t
readByte(uint32_t index) {
  return bytes[index];
}
