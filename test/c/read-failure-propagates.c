
#include<inttypes.h>
#include<stdlib.h>

uint8_t
readByte(uint32_t index) {
  uint8_t* bytes = malloc(5);
  bytes[0] = 2;
  bytes[1] = 3;
  bytes[2] = 4;
  bytes[3] = 5;
  bytes[4] = 6;
  return bytes[index];
}

uint32_t
divideByValue(uint32_t numerator, uint32_t index) {
  return numerator / readByte(index);
}

uint32_t
propagate(uint32_t numerator, uint32_t index) {
  return 1 + readByte(divideByValue(numerator, index));
}

