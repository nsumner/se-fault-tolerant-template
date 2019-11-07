#include "doctest.h"
#include <inttypes.h>

extern "C" {

uint8_t readByte(uint64_t index);

}


TEST_CASE("read malloc byte valid") {
  CHECK(17 == readByte(3));
}


TEST_CASE("read malloc byte invalid") {
  CHECK(0 == readByte(5));
}

