#include <stdbool.h>
#include <stdio.h>
/*
 Using only bit-level and logical operations, write a C expression that is
equivalent to x == y. In other words, it will return 1 when x and y are equal
and 0 otherwise.
*/

bool equal(int x, int y) { return !(x ^ y); }

int main() {
  printf("should be true: %s\n", equal(5, 5) ? "true" : "false");
  printf("should be false: %s\n", equal(5, 4) ? "true" : "false");
}
