
#include<inttypes.h>
#include<stdlib.h>

uint32_t
readOverlap(uint32_t index) {
  uint8_t* bytes = malloc(5);
  bytes[0] = 9;
  bytes[1] = 11;
  bytes[2] = 13;
  bytes[3] = 17;
  bytes[4] = 19;
  uint32_t* asInts = (uint32_t*)bytes;
  return asInts[index];
}
