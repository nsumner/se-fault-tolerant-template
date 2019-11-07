
#include<inttypes.h>

uint8_t
readByte(uint32_t index) {
  uint8_t bytes[5] = {9, 11, 13, 17, 19};
  return bytes[index];
}
