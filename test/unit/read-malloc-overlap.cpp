#include "doctest.h"
#include <inttypes.h>

extern "C" {

uint32_t readOverlap(uint64_t index);

}


TEST_CASE("read malloc overlap valid") {
  CHECK(286067465 == readOverlap(0));
}


TEST_CASE("read malloc overlap invalid") {
  CHECK(0 == readOverlap(1));
}

