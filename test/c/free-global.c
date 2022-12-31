
#include<inttypes.h>

uint8_t global[5] = {3, 5, 7, 9, 11};

uintptr_t
tryFree(uint32_t chooseValid) {
  uint8_t* heap = malloc(5);
  free(chooseValid ? heap : global);
  return (uintptr_t)heap;
}
