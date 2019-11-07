
#include<inttypes.h>
#include<stdlib.h>

uint8_t
readByte(uint32_t index, uint32_t chooseValid) {
  uint8_t* bytes = malloc(5);
  bytes[0] = 9;
  bytes[1] = 11;
  bytes[2] = 13;
  bytes[3] = 17;
  bytes[4] = 19;
  if (chooseValid) {
    return bytes[index];
  }
  free(bytes);
  return bytes[index];
}
