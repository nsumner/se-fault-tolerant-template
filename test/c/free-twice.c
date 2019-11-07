
#include<inttypes.h>
#include<stdlib.h>


uintptr_t
tryFree(uint32_t chooseValid) {
  uint8_t* heap = malloc(5);
  free(heap);
  if (!chooseValid) {
    free(heap);
  }
  return (uintptr_t)heap;
}
