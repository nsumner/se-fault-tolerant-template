
#include<stdio.h>

void
foo(int index) {
  int hmm[10];
  for (unsigned i = 0; i < 10; i++) {
    hmm[i] = index + i;
  }
  int value = hmm[index];
  printf("At index: %d\n", value);
}

int
main(int argc, const char** argv) {
  foo(argc);
  return 0;
}

