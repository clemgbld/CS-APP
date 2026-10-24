#include <stdio.h>

float sum_elements(float a[], unsigned length) {
  int i;
  float result = 0;
  for (i = 0; i < length; i++) {
    result += a[i];
  }
  return result;
}
int main() {
  float a[] = {1, 2, 3};
  printf("%f\n", sum_elements(a, 3));
  float b[] = {};

  printf("%f\n", sum_elements(b, 0));
}
