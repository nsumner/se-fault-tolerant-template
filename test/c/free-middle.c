
#include<inttypes.h>


uintptr_t
tryFree(uint32_t chooseValid) {
  uint8_t* heap = malloc(5);
  free(chooseValid ? heap : (heap + 2));
  return (uintptr_t)heap;
}
