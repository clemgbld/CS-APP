# Chapter 2 Representing and manipulating information

## problem 2.1

Perform the following number conversions

A. 0x25B9D2 to binary

0010 0101 1011 1001 1101 0010

B. binary 1010111001001001 to hexadecimal

0xAE49

C. 0xA8B3D to binary

1010 1000 1011 0011 1101

D. binary 1100100010110110010110 to hexadecimal

x0AE49

## problem 2.2

Fill in the blank entries in the following table, giving the decimal and hexadecimal
representations of different powers of 2:

n         2^n          hex
23        8388608     0x800000
13        8192        0x2000
12        4096        0x1000
8         256         0x100
6         64          0x40
15        32768       0x8000

## problem 2.3

A single byte can be represented by 2 hexadecimal digits. Fill in the missing
entries in the following table, giving the decimal, binary, and hexadecimal values
of different byte patterns:

n       binary           hex
158    1001 1110        0x9E
76     0100 1100        0x4C
145    1001 1100        0x91
174    1010 1110        0xAF
60     0011 1100        0x3C
241    1111 0001        0xF1
117    0111 0101        0x75
189    1011 1101        0xBD
245    1111 0101        0xF5

## problem 2.4

Without converting the numbers to decimal or binary, try to solve the following
arithmetic problems, giving the answers in hexadecimal. Hint: Just modify the
methods you use for performing decimal addition and subtraction to use base 16


A) 0x605C + 0x5 = 0x6061

B) 0X605 - 0x20 = 0x5E5

C) 0x605C + 32 = 0X603C

D) 0x60FA - 0x605C = 0x9E

## problem 2.5

Consider the following three calls to show_bytes:
int a = 0x12345678;
byte_pointer ap = (byte_pointer) &a;
show_bytes(ap, 1); /* A. */
show_bytes(ap, 2); /* B. */
show_bytes(ap, 3); /* C. */
Indicate the values that will be printed by each call on a little-endian machine
and on a big-endian machine:

Little endian    |  Big endian

A) 78            |  12

B) 78 56         |  12 34

C) 78 56 34      |  12 34 56

## problem 2.6

Using show_int and show_float, we determine that the integer 2607352 has hexadecimal
representation 0x0027C8F8, while the floating-point number 3510593.0
has hexadecimal representation 0x4A1F23E0.

A. Write the binary representations of these two hexadecimal values.

0000 0000 0010 0111 1100 1000 1111 1000

0100 1010 0001 1111 0010 0011 1110 0000

B. Shift these two strings relative to one another to maximize the number of
matching bits. How many bits match?

If we shift the 2nd word 2 byte from the right we've got 21 matching bits.

C. What parts of the strings do not match?

We find all the bits of the integer embeded in the floating point number the other part doesn't match.

## problem 2.7

What would be printed as a result of the following call to show_bytes?
const char *m = "mnopqr";
show_bytes((byte_pointer) m, strlen(m));
Note that letters ‘a’ through ‘z’ have ASCII codes 0x61 through 0x7A.

"mnopqr"

6D 6E 6F 70 71 72

## problem 2.8

Fill in the following table showing the results of evaluating Boolean operations on
bit vectors.

a = 010110001
b = 11100001
~a = 10110001
~b = 00011110
a & b = 01000000
a | b = 11101111
a ^ b = 10101111

## problem 2.9

Computers generate color pictures on a video screen or liquid crystal display
by mixing three different colors of light: red, green, and blue. Imagine a simple
scheme, with three different lights, each of which can be turned on or off, projecting
onto a glass screen:

We can then create eight different colors based on the absence (0) or presence
(1) of light sources R, G, and B:

R G B Color
0 0 0 Black
0 0 1 Blue
0 1 0 Green
0 1 1 Cyan
1 0 0 Red
1 0 1 Magenta
1 1 0 Yellow
1 1 1 White

Each of these colors can be represented as a bit vector of length 3, and we can
apply Boolean operations to them.

A. The complement of a color is formed by turning off the lights that are on and
turning on the lights that are off.What would be the complement of each of
the eight colors listed above?

R G B Color
0 0 0 Black -> White
0 0 1 Blue -> Yellow
0 1 0 Green -> Magenta
0 1 1 Cyan -> Red
1 0 0 Red -> Cyan 
1 0 1 Magenta -> Green
1 1 0 Yellow -> Blue
1 1 1 White -> Black


B. Describe the effect of applying Boolean operations on the following colors:

Blue | Green = Cyan
Yellow & Cyan = Green
Red ^ Magenta = Blue

## problem 2.10

As an application of the property that a ^ a = 0 for any bit vector a, consider the
following program:

```c
 void inplace_swap(int *x, int *y) { 
 *y = *x ^ *y; /* Step 1 */
 *x = *x ^ *y; /* Step 2 */
 *y = *x ^ *y; /* Step 3 */
 }
```

As the name implies, we claim that the effect of this procedure is to swap
the values stored at the locations denoted by pointer variables x and y. Note
that unlike the usual technique for swapping two values, we do not need a third
location to temporarily store one value while we are moving the other. There is
no performance advantage to this way of swapping; it is merely an intellectual
amusement.

Starting with values a and b in the locations pointed to by x and y, respectively,
fill in the table that follows, giving the values stored at the two locations after each
step of the procedure. Use the properties of ^ to show that the desired effect is
achieved. Recall that every element is its own additive inverse (that is, a ^ a = 0).

Step  *x                *y
--------------------------------------
Init   a                b
Step1  a                a ^ b
Step2  a^ (a ^b) = b    a ^ b
Step3  b                b ^ (a ^ b) = a



## problem 2.11

Armed with the function inplace_swap from Problem 2.10, you decide to write
code that will reverse the elements of an array by swapping elements from opposite
ends of the array, working toward the middle.
You arrive at the following function:
```c
1 void reverse_array(int a[], int cnt) {
2 int first, last;
3 for (first = 0, last = cnt-1;
4 first <= last;
5 first++,last--)
6 inplace_swap(&a[first], &a[last]);
7 }
```
When you apply your function to an array containing elements 1, 2, 3, and 4,
you find the array now has, as expected, elements 4, 3, 2, and 1. When you try it
on an array with elements 1, 2, 3, 4, and 5, however, you are surprised to see that
the array now has elements 5, 4, 0, 2, and 1. In fact, you discover that the code
always works correctly on arrays of even length, but it sets the middle element to
0 whenever the array has odd length.
A. For an array of odd length cnt= 2k + 1, what are the values of variables
first and last in the final iteration of function reverse_array?

Both variables have the same index.

B. Why does this call to function inplace_swap set the array element to 0?

Because they have the same index, at the end the program end up doing a ^ a which gives 0.

C. What simple modification to the code for reverse_array would eliminate
this problem?

removing the "=" in the "<=" in the for loop like i did [here](./reverse_array.c), the loop will stop before first and last have the same index.

## problem 2.12

[answer](./problem_12.c)

## problem 2.13

The Digital Equipment VAX computer was a very popular machine from the late
1970s until the late 1980s. Rather than instructions for Boolean operations and
and or, it had instructions bis (bit set) and bic (bit clear). Both instructions
take a data word x and a mask word m. They generate a result z consisting of the
bits of x modified according to the bits of m. With bis, the modification
involves setting z to 1 at each bit position where m is 1.With bic, the
modification involves setting z to 0 at each bit position where m is 1. To see
how these operations relate to the C bit-level operations, assume we have
functions bis and bic implementing the bit set and bit clear operations, and
that we want to use these to implement functions computing bitwise operations |
and ^, without using any other C operations. Fill in the missing code below.
Hint: Write C expressions for the operations bis and bic.

```c

/* Compute x|y using only calls to functions bis and bic */
int bool_or(int x, int y) {
  int result = bis(x,y);
  return result;
}
/* Compute x^y using only calls to functions bis and bic */
int bool_xor(int x, int y) {
  int result = bis(bic(x,y),bic(y,x));
  return result;
}

/* Declarations of functions implementing operations bis and bic */
int bis(int x, int m);
int bic(int x, int m);
```

## problem 2.14

Suppose that a and b have byte values 0x55 and 0x46, respectively. Fill in the
following table indicating the byte values of the different C expressions:

Expression        Value
a & b             x044
a | b             0x57
~a | ~b           0xBB
a & !b            0x00
a && b            0x01
a || b            0x01
!a || !b          0x00
a && ~b           0x01

## prolbem 2.15

[answer](./equal.c)

## problem 2.16

Fill in the table below showing the effects of the different shift operations on singlebyte
quantities. The best way to think about shift operations is to work with binary
representations. Convert the initial values to binary, perform the shifts, and then
convert back to hexadecimal. Each of the answers should be 8 binary digits or 2
hexadecimal digits.

a

Hex         Binary
0xD4        1101 0100
0x64        0110 0100
0x72        0111 0010
0x44        0100 0100

a << 2

Binary      Hex
0101 0000   0x50
1001 0000   0x90
1100 1000   0xC8
0001 0000   0x10

a >> 3 (Logical)

Binary      Hex
0001 1010   0x1A
0000 1100   0x0C
0000 1110   0x0E
0000 1000   0x08


a >> 3 (Arithmetic)

Binary      Hex
1111 1010   0xFA
0000 1100   0x0C
0000 1110   0x0E
0000 1000   0x08


