
#include<inttypes.h>

uint64_t
storeByte(uint32_t index, uint8_t value) {
  uint8_t* bytes = malloc(5);
  bytes[0] = 3;
  bytes[1] = 5;
  bytes[2] = 7;
  bytes[3] = 9;
  bytes[4] = 11;

  bytes[index] = value;

  uint64_t simpleHash = 0;
  for (unsigned i = 0; i < 5; ++i) {
    simpleHash = 3*simpleHash + bytes[i]; 
  }
  return simpleHash;
}
