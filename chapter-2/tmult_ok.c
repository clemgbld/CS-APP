#include <limits.h>
#include <stdint.h>

int tmult_ok(int x, int y) {
  int64_t p = (int64_t)x * y;

  return p == (int)p;
}

int main() {}
