#include <stdio.h>

long fib(int n) {
  long tmp;
  long next = 1;
  long prev = 0;
  int i = 1;
  if (n <= 2) {
    goto done;
  }
loop:
  tmp = next;
  next += prev;
  prev = tmp;
  i++;
  if (i < n) {
    goto loop;
  }
done:
  return next;
}

int main() {
  printf("result= %ld\n", fib(1));
  printf("result= %ld\n", fib(2));
  printf("result= %ld\n", fib(3));
  printf("result= %ld\n", fib(4));
  printf("result= %ld\n", fib(5));
  printf("result= %ld\n", fib(6));
  printf("result= %ld\n", fib(7));
}
