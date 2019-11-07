#include "doctest.h"
#include <inttypes.h>

extern "C" {

uintptr_t tryFree(uint32_t chooseValid);

}


TEST_CASE("free global valid") {
  CHECK(0 != tryFree(1));
}


TEST_CASE("free global invalid") {
  CHECK(0 != tryFree(0));
}

