#include "doctest.h"
#include <inttypes.h>

extern "C" {

uint32_t propagate(uint32_t numerator, uint32_t index);

}


TEST_CASE("failure propagates valid") {
  CHECK(6 == propagate(15, 3));
}


TEST_CASE("read malloc byte invalid") {
  CHECK(3 == propagate(15, 5));
}

