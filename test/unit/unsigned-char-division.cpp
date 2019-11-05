#include "doctest.h"


extern "C" {

unsigned char divide(unsigned char,unsigned char);

}


TEST_CASE("unsigned signed char valid") {
  CHECK(3 == divide(10, 3));
}


TEST_CASE("unsigned signed char invalid") {
  CHECK(0 == divide(10, 0));
}

