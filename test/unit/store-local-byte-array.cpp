#include "doctest.h"
#include <inttypes.h>

extern "C" {

uint64_t storeByte(uint32_t index, uint8_t value);

}


TEST_CASE("store local byte valid 1") {
  CHECK(398 == storeByte(0, 2));
}


TEST_CASE("store local byte valid 2") {
  CHECK(470 == storeByte(4, 2));
}


TEST_CASE("store local byte invalid") {
  CHECK(479 == storeByte(13, 123));
}

