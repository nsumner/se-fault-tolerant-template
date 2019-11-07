#include "doctest.h"
#include <inttypes.h>

extern "C" {

uint8_t readByte(uint64_t index, uint32_t chooseValid);

}


TEST_CASE("read malloc after free valid") {
  CHECK(17 == readByte(3, 1));
}


TEST_CASE("read malloc after free invalid") {
  CHECK(0 == readByte(3, 0));
}

