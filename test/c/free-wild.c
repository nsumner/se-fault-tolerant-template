
#include<inttypes.h>


uintptr_t
tryFree(uint32_t chooseValid) {
  uint8_t* heap = malloc(5);
  free(chooseValid ? heap : (uint8_t)0xAbadCAB);
  return (uintptr_t)heap;
}
