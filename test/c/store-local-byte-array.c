
#include<inttypes.h>

uint64_t
storeByte(uint32_t index, uint8_t value) {
  uint8_t bytes[5] = {3, 5, 7, 9, 11};
  bytes[index] = value;

  uint64_t simpleHash = 0;
  for (unsigned i = 0; i < 5; ++i) {
    simpleHash = 3*simpleHash + bytes[i]; 
  }
  return simpleHash;
}
