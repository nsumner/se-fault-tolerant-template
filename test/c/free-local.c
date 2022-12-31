
#include<inttypes.h>


uintptr_t
tryFree(uint32_t chooseValid) {
  uint8_t local[5] = {3, 5, 7, 9, 11};
  uint8_t* heap = malloc(5);
  free(chooseValid ? heap : local);
  return (uintptr_t)heap;
}
