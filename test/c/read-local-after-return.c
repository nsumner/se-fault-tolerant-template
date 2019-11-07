
#include<inttypes.h>

uint8_t*
readByteHelper(uint32_t index) {
  uint8_t bytes[5] = {9, 11, 13, 17, 19};
  return &bytes[index];
}


uint8_t
readByte(uint32_t index, uint32_t chooseValid) {
  uint8_t bytes[5] = {9, 11, 13, 17, 19};
  if (chooseValid) {
    return bytes[index];
  } else {
    return *readByteHelper(index);
  }
}
