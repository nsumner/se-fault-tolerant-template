#include "doctest.h"


extern "C" {

int divide(int,int);

}


TEST_CASE("signed int valid") {
  CHECK(3 == divide(10, 3));
}


TEST_CASE("signed int invalid") {
  CHECK(0 == divide(10, 0));
}

