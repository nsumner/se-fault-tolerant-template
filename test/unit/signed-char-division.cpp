#include "doctest.h"


extern "C" {

char divide(char,char);

}


TEST_CASE("signed char valid") {
  CHECK(3 == divide(10, 3));
}


TEST_CASE("signed char invalid") {
  CHECK(0 == divide(10, 0));
}

