#include <stdio.h>

int fact_do_int(int n) {
  int result = 1;
  do {
    result *= n;
    n = n - 1;
  } while (n > 1);
  return result;
}

long fact_do(long n) {
  long result = 1;
  do {
    result *= n;
    n = n - 1;
  } while (n > 1);
  return result;
}

int main() {

  printf("int result=%d\n", fact_do_int(14));
  printf("long result=%ld\n", fact_do(14));
}
