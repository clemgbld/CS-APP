#include <stdint.h>
#include <stdio.h>

int main() {
  int32_t x = 0x87654321;

  // A) The least significant byte of x, with all other bits set to 0.
  // [0x00000021]

  int32_t least_significant_byte = x & 0xFF;

  printf("A\n");
  printf("%X\n", least_significant_byte);

  // B)All but the least significant byte of x complemented, with the least
  // significant
  // byte left unchanged. [0x789ABC21]

  printf("B\n");
  printf("%X\n", (~x & 0xFFFFFF00) | least_significant_byte);

  // C. The least significant byte set to all ones, and all other bytes of x
  // left unchanged. [0x876543FF]

  printf("C\n");
  printf("%X\n", (x & 0xFFFFFF00) | 0xFF);
}
