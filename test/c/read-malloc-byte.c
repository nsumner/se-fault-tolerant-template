
#include<inttypes.h>
#include<stdlib.h>

uint8_t
readByte(uint32_t index) {
  uint8_t* bytes = malloc(5);
  bytes[0] = 9;
  bytes[1] = 11;
  bytes[2] = 13;
  bytes[3] = 17;
  bytes[4] = 19;
  return bytes[index];
}
