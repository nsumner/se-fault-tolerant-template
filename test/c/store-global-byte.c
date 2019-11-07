
#include<inttypes.h>

uint8_t bytes[5] = {3, 5, 7, 9, 11};

uint64_t
storeByte(uint32_t index, uint8_t value) {
  bytes[index] = value;

  uint64_t simpleHash = 0;
  for (unsigned i = 0; i < 5; ++i) {
    simpleHash = 3*simpleHash + bytes[i]; 
  }

  // Restore the global values
  bytes[0] = 3;
  bytes[1] = 5;
  bytes[2] = 7;
  bytes[3] = 9;
  bytes[4] = 11;

  return simpleHash;
}
