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

## problem 2.17

Hex      Binary      B2U4(x)                    B2T4(x)
0x1      0001        2^0 = 1                    2^0 = 1
0xB      1011        2^3 + 2^1 + 2^0 = 11       2^3 + 2^1 + 2^0 = -5
0x2      0010        2^1 = 2                    2^1 = 2
0x7      0111        2^2 + 2^1 + 2^0 = 7        2^2 + 2^1 + 2^0 = 7
0xC      1100        2^3 + 2^2 = 12             2^3 + 2^2 = -4

## problem 2.18

In Chapter 3, we will look at listings generated by a disassembler, a program that
converts an executable program file back to a more readable ASCII form. These
files contain many hexadecimal numbers, typically representing values in two’scomplement form. Being able to recognize these numbers and understand their
significance (for example, whether they are negative or positive) is an important
skill.
For the lines labeled A–I (on the right) in the following listing, convert the
hexadecimal values (in 32-bit two’s-complement form) shown to the right of the
instruction names (sub, mov, and add) into their decimal equivalents:

0x20 -> 736
-0x58 -> -88
0x28 -> 40
-0x30 -> -48
0x78 -> 120
0x88 -> 136
0x1F8 -> 504
0x8 -> 8
0xC0 -> 192
-0x48 -> -72

## problem 2.19

Using the table you filled in when solving Problem 2.17, fill in the following table
describing the function T2U4:

x          T2U4(x)
-1         15
-5         11
-6         10
-4         12
1          1
8          8

## problem 2.20

Explain how Equation 2.5 applies to the entries in the table you generated when
solving Problem 2.19.

For the first four entries T2U4(x) = x + 2^4

And for the rest T2U4(x) = x.

## problem 2.21

Assuming the expressions are evaluated when executing a 32-bit program on a ma-
chine that uses two’s-complement arithmetic, fill in the following table describing
the effect of casting and relational operations, in the style of Figure 2.19:

Expression                          Type        Evaluation
-2147483647-1 == 2147483648U        unsigned    1 
-2147483647-1 < 2147483647          signed      1
-2147483647-1U < 2147483647         unsigned    0    
-2147483647-1 < -2147483647         signed      1
-2147483647-1U < -2147483647        unsigned    1

## problem 2.22

Show that each of the following bit vectors is a two’s-complement representation
of−4 by applying Equation 2.3:
A. [1100] -> -8 + 4 = -4
B. [11100] -> -16 + 8 + 4 = -4
C. [111100] -> -32 + 16 + 8 + 4 = -8
Observe that the second and third bit vectors can be derived from the first by sign
extension.

## problem 2.23

Consider the following C functions:

```c
int fun1(unsigned word) {
return (int) ((word << 24) >> 24);
}
}
int fun2(unsigned word) {
return ((int) word << 24) >> 24;
```


Assume these are executed as a 32-bit program on a machine that uses two’s-
complement arithmetic. Assume also that right shifts of signed values are per-
formed arithmetically, while right shifts of unsigned values are performed logically.

A. Fill in the following table showing the effect of these functions for several
example arguments. You will find it more convenient to work with a hexa-
decimal representation. Just remember that hex digits 8 through F have their
most significant bits equal to 1.

w             fun1(w)     fun2(w)
0x00000076    0x00000076   0x00000076
0x87654321    0x00000021   0x00000021
0x000000C9    0x000000C9   0xFFFFFFC9
0xEDCBA987    0x00000087   0xFFFFFF87


B. Describe in words the useful computation each of these functions performs.

fun1(w) -> extract the 8 lowest bits the resulting number will be between 0 and 255
fun2(w) -> extract the 8 lowest bits as well but perform sign extension the number will be between -128 and 127.

## problem 2.24

Suppose we truncate a 4-bit value (represented by hex digits 0 through F)toa3-
bit value (represented as hex digits 0 through 7.) Fill in the table below showing
the effect of this truncation for some cases, in terms of the unsigned and two’s-
complement interpretations of those bit patterns.  

Unsigned

1 -> 1
3 -> 3
5 -> 5
12 -> 4
14 -> 6

Two's complement
1 -> 1
3 -> 3
5 -> -3
-4 -> -4
-2 -> -2

Explain how Equations 2.9 and 2.10 apply to these cases.

For unsigned x mod 2^3.
For two's complement U2T3(x mod 2^3).

## problem 2.25

Consider the following code that attempts to sum the elements of an array a, where
the number of elements is given by parameter length:

```c
 /* WARNING: This is buggy code */
 float sum_elements(float a[], unsigned length) {
 int i;
 float result = 0;

 for (i = 0; i <= length-1; i++)
 result += a[i];
 return result;
 }
```

When run with argument length equal to 0, this code should return 0.0.
Instead, it encounters a memory error. Explain why this happens. 

It happens because the number 0 - 1 overflow on the left for unsigned integer and become U_INTEGER_MAX which a very big number because it is all 32 bits turned to 1.
and then the for loop execute and try to access the index of an empty array and then provoking a memory error.

Show how this code can be corrected.

(answer)[./sum_elements.c]

## problem 2.26

You are given the assignment of writing a function that determines whether one
string is longer than another. You decide to make use of the string library function
strlen having the following declaration:

```c

/* Prototype for library function strlen */
size_t strlen(const char *s);
Here is your first attempt at the function:
/* Determine whether string s is longer than string t */
/* WARNING: This function is buggy */
int strlonger(char *s, char *t) {
return strlen(s) - strlen(t) > 0;
}
```

When you test this on some sample data, things do not seem to work quite
right. You investigate further and determine that, when compiled as a 32-bit

program, data type size_t is defined (via typedef) in header file stdio.h to be
unsigned.
A. For what cases will this function produce an incorrect result?

When t is longer than s.

B. Explain how this incorrect result comes about.

Because when an unsigned integer become negative it overflow on the left and become a big number.

C. Show how to fix the code so that it will work reliably.

```c
int strlonger(char *s, char *t) {
return strlen(s) > strlen(t);
}
```

## problem 2.27

/* Determine whether arguments can be added without overflow */
```c
int uadd_ok(unsigned x, unsigned y);
```

[answer](./uadd_ok.c)

## problem 2.28

We can represent a bit pattern of length w = 4 with a single hex digit. For an
unsigned interpretation of these digits, use Equation 2.12 to fill in the following
table giving the values and the bit representations (in hex) of the unsigned additive
inverses of the digits shown.

        x                -u/4 x
Hex      Decimal        Decimal     Hex              
1          1            15          F
4          4            12          C
7          7             9          9
A          10            6          6
E          14            2          2


## problem 2.29

Fill in the following table in the style of Figure 2.25. Give the integer values of
the 5-bit arguments, the values of both their integer and two’s-complement sums,
the bit-level representation of the two’s-complement sum, and the case from the
derivation of Equation 2.13.

x                   y              x + y         x + t/5 y          case
12               15                -27            5
10100            10001            100101         00101               1
-8               -8                -16            -16 
11000            11000            110000         10000               2
-9                8                -1             -1
10111            01000            111111         11111               2
 2                5                 7             7
00010            00101            000111         00111               3
12                4                16            -16 
10100            00100            010000         10000               4

## problem 2.30

Write a function with the following prototype:
/* Determine whether arguments can be added without overflow */

```c
int tadd_ok(int x, int y);
```

This function should return 1 if arguments x and y can be added without
causing overflow.

```c
int tadd_ok(int x, int y){
  int sum = x + y;
  bool pos_overflow = x > 0 && y > 0 && x + y <= 0;
  bool neg_overflow = x < 0 && y < 0 && x + y >= 0;
  return !pos_overflow && !neg_overflow;
};
```


## problem 2.31

Your coworker gets impatient with your analysis of the overflow conditions for
two’s-complement addition and presents you with the following implementation
of tadd_ok:

```c
/* Determine whether arguments can be added without overflow */
/* WARNING: This code is buggy. */
int tadd_ok(int x, int y) {
int sum = x+y;
return (sum-x == y) && (sum-y == x);
}
```


Because (x + y) - x will always evaluate to y and (x + y) - y will always evaluate to x regardless of any overflow.


## problem 2.32

You are assigned the task of writing code for a function tsub_ok, with arguments
x and y, that will return 1 if computing x-y does not cause overflow. Having just
written the code for Problem 2.30, you write the following:

```c
/* Determine whether arguments can be subtracted without overflow */
/* WARNING: This code is buggy. */
int tsub_ok(int x, int y) {
return tadd_ok(x, -y);
}
```


For what values of x and y will this function give incorrect results? Writing a
correct version of this function is left as an exercise (Problem 2.74).

When  y is TMIN as well.

## problem 2.33

We can represent a bit pattern of length w = 4 with a single hex digit. For a two’s-
complement interpretation of these digits, fill in the following table to determine
the additive inverses of the digits shown:
x                   -t/4 x
Hex    Decimal      Decimal   Hex
2      2            -2        E     
3      3            -3        D     
9      9            -9        7     
B      11            5        5     
C      12            4        4     

What do you observe about the bit patterns generated by two’s-complement
and unsigned (Problem 2.28) negation?

They are the same.

## problem 2.34

Fill in the following table showing the results of multiplying different 3-bit num-
bers, in the style of Figure 2.27:

Mode     x            y           x * y         truncated
u      4 100        5  101       20 010100      4 100
t     -4 100        -3  101      12 001100     -4 100


u      2 010        7  111       14 001110      6 110
t      2 010       -1  111       -2 111110     -2 110


u      6 110        6  110       12 001100      4 100
t     -2 110       -2  110       4  000100     -4 100


## problem 2.36

You are given the assignment to develop code for a function tmult_ok that will
determine whether two arguments can be multiplied without causing overflow.
Here is your solution:

```c
/* Determine whether arguments can be multiplied without overflow */
int tmult_ok(int x, int y) {
int p = x*y;
/* Either x is zero, or dividing p by x gives y */
return !x || p/x == y;
}
```


You test this code for a number of values of x and y, and it seems to work
properly. Your coworker challenges you, saying, “If I can’t use subtraction to
test whether addition has overflowed (see Problem 2.31), then how can you use
division to test whether multiplication has overflowed?”
Devise a mathematical justification of your approach, along the following
lines. First, argue that the case x = 0 is handled correctly. Otherwise, consider
w-bit numbers x (x ̸= 0), y, p, and q, where p is the result of performing two’s-
complement multiplication on x and y, and q is the result of dividing p by x.

1. Show that x . y, the integer product of x and y, can be written in the form
x . y= p + t2w, where t ̸= 0 if and only if the computation of p overflows.

x * y = p only and only t = 0 so if p overflow it has to be x * y = p +t2w

2. Show that p can be written in the form p= x . q + r, where |r| < |x|.

p / x = q + r if we take the formula in the code

p = x * q + r

3. Show that q= y if and only if r = t = 0. 

x * y = x * q = y = q

## problem 2.36

For the case where data type int has 32 bits, devise a version of tmult_ok (Prob-
lem 2.35) that uses the 64-bit precision of data type int64_t, without using
division.

[answer](./tmult_ok.c)

## problem 2.37

ou are given the task of patching the vulnerability in the XDR code shown in
the aside on page 136 for the case where both data types int and size_t are 32
bits. You decide to eliminate the possibility of the multiplication overflowing by
computing the number of bytes to allocate using data type uint64_t. You replace

the original call to malloc (line 9) as follows:

```c
uint64_t asize =
ele_cnt * (uint64_t) ele_size;
void *result = malloc(asize);

```

A. Recall that the argument to malloc has type size_t.
Does your code provide any improvement over the original?

No it doesn't because size_t is architecture dependent so if it is a 32 bits system the result will be the same.


B. How would you change the code to eliminate the vulnerability?

the right approach is to check if ele_cnt * ele_size is within SIZE_MIN and SIZE_MAX.

```c
uint64_t asize = ele_cnt * (uint64_t)  ele_size;

size_t size = (size_t) asize;

if(asize != size){
  return NULL;
}
void *result = malloc(asize);

```


## problem 2.38

As we will see in Chapter 3, the lea instruction can perform computations of
the form (a<<k) + b, where k is either 0, 1, 2, or 3, and b is either 0 or some
program value. The compiler often uses this instruction to perform multiplications
by constant factors. For example, we can compute 3*a as (a<<1) + a.
Considering cases where b is either 0 or equal to a, and all possible values of k,
what multiples of a can be computed with a single lea instruction?

1, 2 ,4, 8
3,5,9

## problem 2.39

How could we modify the expression for form B for the case where bit position n
is the most significant bit?

-(x << m)

## problem 2.40

 For each of the following values of K, find ways to express x*K using only the
specified number of operations, where we consider both additions and subtrac-
tions to have comparable cost. You may need to use some tricks beyond the simple
form A and B rules we have considered so far.

K       Shifts    Add/Subs           Expression
7       1           1                (x << 3) - x
30      4           3                (x << 4) + (x << 3) + (x << 2<) + (x << 1)
28      2           1                (x << 5) - (x << 2)
55      2           2                (x << 6) - (x << 3) - x

## problem 2.41

For a run of ones starting at bit position n down to bit position m (n ≥ m), we saw
that we can generate two forms of code, A and B. How should the compiler decide
which form to use?

Choose A when n = m else choose B.

## problem 2.42

Write a function div16 that returns the value x/16 for integer argument x. Your
function should not use division, modulus, multiplication, any conditionals (if or
?:), any comparison operators (e.g., <, >,or==), or any loops. You may assume
that data type int is 32 bits long and uses a two’s-complement representation, and
that right shifts are performed arithmetically.

[answer](./div16.c)

## problem 2.43

In the following code, we have omitted the definitions of constants M and N:

```c
#define M /* Mystery number 1 */
#define N /* Mystery number 2 */
int arith(int x, int y) {
int result = 0;
result = x*M + y/N; /* M and N are mystery numbers. */
return result;
}
```


We compiled this code for particular values of M and N. The compiler opti-
mized the multiplication and division using the methods we have discussed. The
following is a translation of the generated machine code back into C:

```c
/* Translation of assembly code for arith */
int optarith(int x, int y) {
int t=x;
x <<= 5;
x-=t;
if(y<0)y+=7;
y >>= 3; /* Arithmetic shift */
return x+y;
}
```


What are the values of M and N?

M = 31 and N = 8.

## problem 2.44

Assume data type int is 32 bits long and uses a two’s-complement representation
for signed values. Right shifts are performed arithmetically for signed values and
logically for unsigned values. The variables are declared and initialized as follows:
```c
int x = foo(); int y = bar(); /* Arbitrary value */
/* Arbitrary value */
unsigned ux = x;
unsigned uy = y;

```
For each of the following C expressions, either (1) argue that it is true (evalu-
ates to 1) for all values of x and y, or (2) give values of x and y for which it is false
(evaluates to 0):
A. (x>0)||(x-1<0)
False
B. (x & 7) != 7 || (x<<29 < 0)
True
C. (x*x)>=0
False
D. x<0||-x<=0
True
E. x>0||-x>=0
False
F. x+y == uy+ux
True
G. x*~y + uy*ux == -x
True

## problem 2.45

Fill in the missing information in the following table:

3/4     0.11      0.75
5/16    0.0101    0.3125
43/16   10.1011   2.6875
9/8     1.001     1.125
47/8    101.111   5.875
51/16   11.0011   3.1875

## problem 2.46

The imprecision of floating-point arithmetic can have disastrous effects. On Febru-
ary 25, 1991, during the first Gulf War, an American Patriot Missile battery in
Dharan, Saudi Arabia, failed to intercept an incoming Iraqi Scud missile. The
Scud struck an American Army barracks and killed 28 soldiers. The US General
Accounting Office (GAO) conducted a detailed analysis of the failure [76] and de-
termined that the underlying cause was an imprecision in a numeric calculation.
In this exercise, you will reproduce part of the GAO’s analysis.
The Patriot system contains an internal clock, implemented as a counter
that is incremented every 0.1 seconds. To determine the time in seconds, the
program would multiply the value of this counter by a 24-bit quantity that was
a fractional binary approximation to 1
10 . In particular, the binary representation
of 1
10 is the nonterminating sequence 0.000110011[0011]...2, where the portion in
brackets is repeated indefinitely. The program approximated 0.1, as a value x,by
considering just the first 23 bits of the sequence to the right of the binary point:
x = 0.00011001100110011001100. (See Problem 2.51 for a discussion of how they
could have approximated 0.1 more precisely.)
A. What is the binary representation of 0.1− x?

0.000000000000000000000001100[1100]..2
B. What is the approximate decimal value of 0.1− x?

9.54 * 10^-8

C. The clock starts at 0 when the system is first powered up and keeps counting

0.343 seconds

up from there. In this case, the system had been running for around 100 hours.
What was the difference between the actual time and the time computed by
the software?
D. The system predicts where an incoming missile will appear based on its
velocity and the time of the last radar detection. Given that a Scud travels
at around 2,000 meters per second, how far off was its prediction?

0.343 * 2000 around 687m

Normally, a slight error in the absolute time reported by a clock reading would
not affect a tracking computation. Instead, it should depend on the relative time
between two successive readings. The problem was that the Patriot software had
been upgraded to use a more accurate function for reading time, but not all of
the function calls had been replaced by the new code. As a result, the tracking
software used the accurate time for one reading and the inaccurate time for the
other.
