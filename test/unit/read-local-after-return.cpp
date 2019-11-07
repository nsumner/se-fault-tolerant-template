#include "doctest.h"
#include <inttypes.h>

extern "C" {

uint8_t readByte(uint32_t index, uint32_t chooseValid);

}


TEST_CASE("read local after return valid") {
  CHECK(17 == readByte(3, 1));
}


TEST_CASE("read local after return invalid") {
  CHECK(0 == readByte(3, 0));
}

