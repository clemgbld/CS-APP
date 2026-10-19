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


