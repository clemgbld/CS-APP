#include <stdio.h>

void inplace_swap(int *x, int *y) {
  *y = *x ^ *y;
  *x = *x ^ *y;
  *y = *x ^ *y;
}

void reverse_array(int a[], int cnt) {
  int first, last;
  for (first = 0, last = cnt - 1; first < last; first++, last--) {
    inplace_swap(&a[first], &a[last]);
  }
}

void print_num_array(int a[], int cnt) {
  for (int i = 0; i < cnt; i++) {
    printf("%d", a[i]);
  }
  printf("\n");
}

int main() {

  int a[] = {1, 2, 3, 4};

  int b[] = {1, 2, 3, 4, 5};

  reverse_array(a, 4);

  reverse_array(b, 5);

  print_num_array(a, 4);

  print_num_array(b, 5);
}
