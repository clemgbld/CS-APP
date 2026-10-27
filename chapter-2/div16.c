#include <stdio.h>

int div16(int x) {
  int k = 4;
  int bias = (x >> 31) & 0xF;
  return (x + bias) >> k;
}

int main() {
  printf("%d\n", div16(32));
  printf("%d\n", div16(-32));
  printf("%d\n", div16(-12340));
}
