# Chapter 3 Machine-level representation of programs

## problem 3.1

Assume the following values are stored at the indicated memory addresses and
registers:
Address Value Register Value
0x100 0xFF %rax 0x100
0x104 0xAB %rcx 0x1
0x108 0x13 %rdx 0x3
0x10C 0x11
Fill in the following table showing the values for the indicated operands:

Operand         Value
%rax            0x100
0x104           0xAB
$0x108          0x108
(%rax)          0xFF
4(%rax)         0xAB
9(%rax,%rdx)    0x11
260(%rcx,%rdx)  0x13
0xFC(,%rcx,4)   0xFF
(%rax,%rdx,4)   0x11

## problem 3.2

For each of the following lines of assembly language, determine the appropriate
instruction suffix based on the operands. (For example, mov can be rewritten as
movb, movw, movl,ormovq.)

movl %eax, (%rsp)
movw (%rax), %dx
movb $0xFF, %bl
movb (%rsp,%rdx,4), %dl
movq (%rdx), %rax
movw %dx, (%rax)

Each of the following lines of code generates an error message when we invoke
the assembler. Explain what is wrong with each line.

movb $0xF, (%ebx) -> Cannot use %ebx as register address
movl %rax, (%rsp) -> Mismatch between instruction suffix and register id
movw (%rax),4(%rsp) -> Cannot copy memory into memory
movb %al,%sl -> Register %sl doesn't exist
movq %rax,$0x123 -> Cannot copy into Immediate
movl %eax,%rdx -> Mismatch between source size and destination size
movb %si, 8(%rbp) -> Mismatch between instruction suffix and register id

## problem 3.4

Assume variables sp and dp are declared with types

src_t *sp;
dest_t *dp;

where src_t and dest_t are data types declared with typedef. We wish to use
the appropriate pair of data movement instructions to implement the operation

*dp = (dest_t) *sp;

Assume that the values of sp and dp are stored in registers %rdi and %rsi,
respectively. For each entry in the table, show the two instructions that implement
the specified data movement. The first instruction in the sequence should read
from memory, do the appropriate conversion, and set the appropriate portion of
register %rax. The second instruction should then write the appropriate portion
of %rax to memory. In both cases, the portions may be %rax, %eax, %ax,or%al,
and they may differ from one another.
Recall that when performing a cast that involves both a size change and a
change of “signedness” in C, the operation should change the size first (Section
2.2.6).

long  long 

movq (%rdi), %rax
movq %rax, (%rsi)

char  int   

movsbl (%rdi), %eax
movl %eax, (%rsi)

char unsigned

movzbl (%rdi), %eax
movl %eax, (%rsi)

unsigned char  long

movzbq (%rdi), %eax
movq %rax, (%rsi)

int   char

movl (%rdi), %eax
movb %al, (%rsi)

unsigned unsigned char

movl (%rdi), %eax
movb %al, (%rsi)

char   short

movsbw (%rdi), %ax
movw %ax, (%rsi)

## problem 3.5

You are given the following information. A function with prototype
void decode1(long *xp, long *yp, long *zp);
is compiled into assembly code, yielding the following:

void decode1(long *xp, long *yp, long *zp)

xp in %rdi, yp in %rsi, zp in %rdx

decode1:
movq (%rdi), %r8
movq (%rsi), %rcx
movq (%rdx), %rax
movq %r8, (%rsi)
movq %rcx, (%rdx)
movq %rax, (%rdi)
ret

Parameters xp, yp, and zp are stored in registers %rdi, %rsi, and %rdx, respec-
tively.
Write C code for decode1 that will have an effect equivalent to the assembly code shown.

```c
void decode1(long *xp, long *yp, long *zp){
    long x = *xp;
    long y = *yp;
    long z = *zp;
    *yp = x;
    *zp = y;
    *xp = z;
}
```

## problem 3.6

Suppose register %rbx holds value p and %rdx holds value q. Fill in the table below
with formulas indicating the value that will be stored in register %rax for each of
the given assembly-code instructions:

Instruction                     Result
leaq 9(%rdx), %rax              q  + 9
leaq (%rdx,%rbx), %rax          p + q
leaq (%rdx,%rbx,3), %rax        3p + q
leaq 2(%rbx,%rbx,7), %rax       8p + 2
leaq 0xE(,%rdx,3), %rax         3q + 14
leaq 6(%rbx,%rdx,7), %rax       7q + p + 6


## problem 3.7

Consider the following code, in which we have omitted the expression being
computed:

```c
short scale3(short x, short y, short z) {
short t = ;
return t;
}
```


Compiling the actual function with gcc yields the following assembly code:

short scale3(short x, short y, short z)

x in %rdi, y in %rsi, z in %rdx

```
scale3:
leaq (%rsi,%rsi,9), %rbx
leaq (%rbx,%rdx), %rbx
leaq (%rbx,%rdi,%rsi), %rbx
ret
```

Fill in the missing expression in the C code.

```c
short scale3(short x, short y, short z) {
short t = 10 * y + z + x * y;
return t;
}
```

## problem 3.8

Assume the following values are stored at the indicated memory addresses and
registers:

Address    Value      Register     Value
0x100      0xFF       %rax         0x100
0x108      0xAB       %rcx         0x1
0x110      0x13       %rdx         0x3
0x118      0x11

Fill in the following table showing the effects of the following instructions,
in terms of both the register or memory location that will be updated and the
resulting value:

Instruction                Destination     Value
addq %rcx,(%rax)           0x100           0x100
subq %rdx,8(%rax)          0x108           0xA8
imulq $16,(%rax,%rdx,8)    0x118           0xBB
incq 16(%rax)              0x110           0x14
decq %rcx                  %rcx            0x0
subq %rdx,%rax             %rax            0xFD

## problem 3.9

Suppose we want to generate assembly code for the following C function:

```c
long shift_left4_rightn(long x, long n)
{
x <<= 4;
x >>= n;
return x;
}
```

The code that follows is a portion of the assembly code that performs the
actual shifts and leaves the final value in register %rax. Two key instructions
have been omitted. Parameters x and n are stored in registers %rdi and %rsi,
respectively.

long shift_left4_rightn(long x, long n)
x in %rdi, n in %rsi

shift_left4_rightn:
movq %rdi, %rax     Get x
shlq $4,   %rax     x << 4
movl %esi, %ecx     Get n (4 bytes)
sarq %cl, %rax     x >> n

Fill in the missing instructions, following the annotations on the right. The
right shift should be performed arithmetically.

## problem 3.10

Consider the following code, in which we have omitted the expression being
computed:

```c
short arith3(short x, short y, short z)
{
short p1 = y | z;
short p2 = p1 >> 9;
short p3 = ~p2;
short p4 = y - p3;
return p4;
}
```

The portion of the generated assembly code implementing these expressions
is as follows:

short arith3(short x, short y, short z)
x in %rdi, y in %rsi, z in %rdx
arith3:
orq %rsi, %rdx
sarq $9, %rdx
notq %rdx
movq %rdx, %bax
subq %rsi, %rbx
ret

Based on this assembly code, fill in the missing portions of the C code.

## problem 3.11

It is common to find assembly-code lines of the form
xorq %rcx,%rcx

in code that was generated from C where no exclusive-or operations were
present.

A. Explain the effect of this particular exclusive-or instruction and what useful
operation it implements.

It implements a bitwise operation non exclusive or with a register and itself (eg. x ^ x).

B. What would be the more straightforward way to express this operation in
assembly code?

movq $0, rcx

C. Compare the number of bytes to encode any two of these three different
implementations of the same operation.


xorq %rcx,%rcx -> 3 bytes 
movq $0, rcx -> 7 bytes

## problem 3.12

Consider the following function for computing the quotient and remainder of two
unsigned 64-bit numbers:

void uremdiv(unsigned long x, unsigned long y,
unsigned long *qp, unsigned long *rp) {
unsigned long q = x/y;
unsigned long r = x%y;
*qp=q;
*rp=r;
}

Modify the assembly code shown for signed division to implement this function.

1 remdiv:
2 movq %rdx, %r8
3 movq %rdi, %rax
4 movl $0, %edx
5 divq %rsi
6 movq %rax, (%r8)
7 movq %rdx, (%rcx)
8 ret


## problem 3.13

The C code

```c
int comp(data_t a, data_t b) {
return a COMP b;
}
```


shows a general comparison between arguments a and b, where data_t, the data
type of the arguments, is defined (via typedef) to be one of the integer data types
listed in Figure 3.1 and either signed or unsigned. The comparison COMP is defined
via #define.
Suppose a is in some portion of %rdx while b is in some portion of %rsi.For
each of the following instruction sequences, determine which data types data_t
and which comparisons COMP could cause the compiler to generate this code.
(There can be multiple correct answers; you should list them all.)


A. cmpl %esi, %edi
setl %al

data_t = int 
COMP = <

B. cmpw %si, %di
setge %al

data_t = short
COMP = >=

C. cmpb %sil, %dil
setbe %al

data_t =  unsigned char
COMP = <=

D. cmpq %rsi, %rdi
setne %al

data_t = long, char *, unsigned long
COMP = !=


## problem 3.14

The C code

```c
int test(data_t a) {
return a TEST 0;
}
```

shows a general comparison between argument a and 0, where we can set the
data type of the argument by declaring data_t with a typedef, and the nature
of the comparison by declaring TEST with a #define declaration. The following
instruction sequences implement the comparison, where a is held in some portion
of register %rdi. For each sequence, determine which data types data_t and which
comparisons TEST could cause the compiler to generate this code. (There can be
multiple correct answers; list all correct ones.)

A. testq  %rdi, %rdi
setge %al

data_t = long
TEST = >=

B. testw  %di, %di
sete %al

TEST = ==
data_t = short, unsigned short

C. testb  %dil, %dil
seta %al

data_t = unsigned char
TEST =  >

D. testl  %edi, %edi
setle %al

data_t = int
TEST = <=

## problem 3.15

In the following excerpts from a disassembled binary, some of the information has
been replaced by X’s. Answer the following questions about these instructions.
c
A. What is the target of the je instruction below? (You do not need to know
anything about the callq instruction here.)

4003fa: 74 02 je  4003fe <loop+0x2>
4003fc: ff d0 callq *%rax

B. What is the target of the je instruction below?
40042f: 74 f4 je 400425 <loop+0xf4>
400431: 5d pop %rbp

C. What is the address of the ja and pop instructions?
400543: 77 02 ja 400547
400545 5d pop %rbp

D. In the code that follows, the jump target is encoded in PC-relative form as a 4-
byte two’s-complement number. The bytes are listed from least significant to
most, reflecting the little-endian byte ordering of x86-64. What is the address
of the jump target?

4005e8: e9 73 ff ff ff jmpq 400560 <loop+0xff73>
4005ed: 90 nop

## problem 3.16

When given the C code

```c
void cond(short a, short *p)
{
if (a && *p < a)
*p=a;
}
```

gcc generates the following assembly code:

void cond(short a, short *p)
a in %rdi, p in %rsi

cond:
testq %rdi, %rdi
je .L1
cmpq %rsi, (%rdi)
jle .L1
movq %rdi, (%rsi)
.L1:
rep; ret

A. Write a goto version in C that performs the same computation and mimics
the control flow of the assembly code, in the style shown in Figure 3.16(b).
You might find it helpful to first annotate the assembly code as we have done
in our examples.

```c
void cond(short a, short*p){
  if(a == 0){
    goto L1;
  }
  if(a <= *p){
    goto L1;
  }
  *p=a; 
  L1:
    return;
}
```

B. Explain why the assembly code contains two conditional branches, even
though the C code has only one if statement.

Because we need first to check if a is not zero and then if a <= *p in assembly that can't be done in one operation.

## problem 3.17

An alternate rule for translating if statements into goto code is as follows:

```c
t=test-expr;
if (t)
goto true;
else-statement
goto done;
true:
then-statement
done:
```

A) Rewrite the goto version of absdiff_se based on this alternate rule.

```c
long gotodiff_se(long x, long y){
  long result;
  if(x < y){
    goto x_l_y;
  }else{
     ge_cnt++;
    result = x - y;
    return result;
   goto x_ge_y;
  }
  x_l_y:
    lt_cnt++;
    result = y - x;
    return result;
}
```

B) Can you think of any reasons for choosing one rule over the other?

The choice is purely arbitrary i would say.

## problem 3.18

Starting with C code of the form
```c
short test(short x, short y, short z) {
  short val = (y + z) - x;
    if (z > 5){
      if (y <= 2)
        val = x / y;
      else
      val = x / z;
    } else if (z < 3)
      val = z / y;
    return val;
}
```


gcc generates the following assembly code:

short test(short x, short y, short z)
x in %rdi, y in %rsi, z in %rdx
test:
leaq (%rdx,%rsi), %rax
subq %rdi, %rax
cmpq $5, %rdx
jle .L2
cmpq $2, %rsi
jle .L3
movq %rdi, %rax
idivq %rdx, %rax
ret
.L3:
movq %rdi, %rax
idivq %rsi, %rax
ret
.L2:
cmpq $3, %rdx
jge .L4
movq %rdx, %rax
idivq %rsi, %rax
.L4:
rep; ret

Fill in the missing expressions in the C code.

## problem 3.19

Running on a new processor model, our code required around 45 cycles when the
branching pattern was random, and around 25 cycles when the pattern was highly
predictable.

A. What is the approximate miss penalty?
2(45 - 25) = 40

B. How many cycles would the function require when the branch is mispre-
dicted?

25 + 40 = 65

## problem 3.20

In the following C function, we have left the definition of operation OP incomplete:

```c
#define OP /* Unknown operator */
short arith(short x) {
return x OP 16;
}
```

When compiled, gcc generates the following assembly code:

short arith(short x)
x in %rdi
arith:
leaq 15(%rdi), %rbx  # add 15 for negative numbers
testq %rdi, %rdi   # test x 
cmovns %rdi, %rbx  # if x is positive don't add 15
sarq $4, %rbx  # x >> 4
ret

A) What operation is OP?

```c
#define OP /* Unknown operator */
short arith(short x) {
return x / 16;
}
```

B) Annotate the code to explain how it works.

## problem 3.21
Starting with C code of the form

```c
short test(short x, short y) {
short val = 12 + y;
  if (x < 0){
    if (x >= y)
      val = x | y;
    else
      val = x * y;
  } else if (y >= 10)
      val = x / y;
  return val;
}
```

gcc generates the following assembly code:

short test(short x, short y)
  x in %rdi, y in %rsi

test:
leaq 12(%rsi), %rbx
testq %rdi, %rdi
jge .L2
movq %rdi, %rbx
imulq %rsi, %rbx
movq %rdi, %rdx
orq %rsi, %rdx
cmpq %rsi, %rdi
cmovge %rdx, %rbx
ret
.L2:
idivq %rsi, %rdi
cmpq $10, %rsi
cmovge %rdi, %rbx
ret

Fill in the missing expressions in the C code.


## problem 3.22


A) Try to calculate 14! with a 32-bit int. Verify whether the computation of 14! overflows.

Yes it overflows tested in ./fact_do.c

B) What if the computation is done with a 64-bit long int?

It doesn't overflow in that case.


## problem 3.23

For the C code

```c
short dw_loop(short x) {
short y = x/9;
short *p = &x;
short n = 4*x;
do {
x+=y;
(*p) += 5;
n-=2;
} while (n > 0);
return x;
}
```

gcc generates the following assembly code:

short dw_loop(short x)
x initially in %rdi
1 dw_loop:
2 movq %rdi, %rbx  #stays x
3 movq %rdi, %rcx #int y
4 idivq $9, %rcx #y = x / 9;
5 leaq (,%rdi,4), %rdx # int n = 4 * x;
6 .L2: # do
7 leaq 5(%rbx,%rcx), %rbx x+= 5 + y;
8 subq $2, %rdx   #n-= 2
9 testq %rdx, %rdx #while(n > 0)
10 jg .L2
11 rep; ret # return x

A) Which registers are used to hold program values x, y, and n?

%rcx holds y, %rdx holds n, %rbx holds x

B) How has the compiler eliminated the need for pointer variable p and the
pointer dereferencing implied by the expression (*p)+=5?

it does it in one operation leaq 5(%rbx,%rcx), %rbx aka x+= 5 + y


the compiler do it in one shot

C) Add annotations to the assembly code describing the operation of the pro-
gram, similar to those shown in Figure 3.19(c).

## problem 3.24

For C code having the general form

```c
short loop_while(short a, short b)
{
short result = 0;
while (a > b){
  result = result + (a * b);
  a= a - 1;
}
return result;
}
```

gcc, run with command-line option -Og, produces the following code:

short loop_while(short a, short b)
a in %rdi, b in %rsi
1 loop_while:
2 movl $0, %eax
3 jmp .L2
4 .L3:
5 leaq (,%rsi,%rdi), %rdx
6 addq %rdx, %rax
7 subq $1, %rdi
8 .L2:
9 cmpq %rsi, %rdi
10 jg .L3
11 rep; ret

We can see that the compiler used a jump-to-middle translation, using the jmp
instruction on line 3 to jump to the test starting with label .L2. Fill in the missing
parts of the C code.

## problem 3.25

 For C code having the general form

```c
long loop_while2(long a, long b)
{
long result = b;
while (b > 0){
  result = a * result;
  b= b - a;
}
return result;
}
```

gcc, run with command-line option -O1, produces the following code:
a in %rdi, b in %rsi
1 loop_while2:
2 testq %rsi, %rsi
3 jle .L8
4 movq %rsi, %rax
5 .L7:
6 imulq %rdi, %rax
7 subq %rdi, %rsi
8 testq %rsi, %rsi
9 jg .L7
10 rep; ret
11 .L8:
12 movq %rsi, %rax
13 ret

We can see that the compiler used a guarded-do translation, using the jle
instruction on line 3 to skip over the loop code when the initial test fails. Fill in
the missing parts of the C code. Note that the control structure in the assembly
code does not exactly match what would be obtained by a direct translation of the
C code according to our translation rules. In particular, it has two different ret
instructions (lines 10 and 13). However, you can fill out the missing portions of
the C code in a way that it will have equivalent behavior to the assembly code.

## problem 3.26

 A function test_one has the following overall structure:
```c
short test_one(unsigned short x) {
  short val = 1;
  while (x != 0) {
  val^= x;
  x>>= 1;
  }
  return val & 0;
}
```

 The gcc C compiler generates the following assembly code:
short test_one(unsigned short x)
x in %rdi

test_one:
movl $1, %eax
jmp .L5
.L6:
xorq %rdi, %rax
shrq %rdi 
.L5:
testq %rdi, %rdi
jne .L6
andl $0, %eax
ret

Reverse engineer the operation of this code and then do the following:

A) Determine what loop translation method was used.

It is a classic while loop translation.

B) Use the assembly-code version to fill in the missing parts of the C code.

C) Describe in English what this function computes.

it computes the parity of the argument x.

## problem 3.27

Write goto code for a function called fibonacci to print fibonacci numbers using
a while loop. Apply the guarded-do transformation.

./fib.c

## problem 3.28

A function test_two has the following overall structure:

```c
short test_two(unsigned short x) {
short val = 0;
short i;
for(i = 64;i != 0;i--){
  val= (val << 1) | x & 0x1;
  x>>= 1;
}
return val;
}
```

The gcc C compiler generates the following assembly code:

test fun_b(unsigned test x)
x in %rdi
1 test_two:
2 movl $1, %edx
3 movl $65, %eax
4 .L10:
5 movq %rdi, %rcx
6 andl $1, %ecx
7 addq %rax, %rax
8 orq %rcx, %rax
9 shrq %rdi Shift right by 1
10 addq $1, %rdx
11 jne .L10
12 rep; ret

Reverse engineer the operation of this code and then do the following:

A) Use the assembly-code version to fill in the missing parts of the C code.

B) Explain why there is neither an initial test before the loop nor an initial jump to the test portion of the loop.

Because the loop stop when i is equal at O after an operation.

C) Describe in English what this function computes.

It reverse the bits in x.

## problem 3.29

Executing a continue statement in C causes the program to jump to the end of
the current loop iteration. The stated rule for translating a for loop into a while
loop needs some refinement when dealing with continue statements. For example,
consider the following code:

```c
/* Example of for loop containing a continue statement */
/* Sum even numbers between 0 and 9 */
long sum = 0;
long i;
for (i = 0; i < 10; i++) {
if (i & 1)
continue;
sum += i;
}
```

A) What would we get if we naively applied our rule for translating the for loop
into a while loop? What would be wrong with this code?

It would loop forever because we need to update  i before using going back at the beginning of the loop.

B) How could you replace the continue statement with a goto statement to
ensure that the while loop correctly duplicates the behavior of the for loop?

```c
long sum = 0;
long i = 0;

loop:
if(i >= 10){
  goto done;
}
if(i & 1){
  goto continue;
}
sum+= i;
continue:
  i++;
goto loop;

done:

```

## problem 3.30

In the C function that follows, we have omitted the body of the switch statement.
In the C code, the case labels did not span a contiguous range, and some cases had
multiple labels.

```c
void switch2(short x, short *dest) {
short val = 0;
switch (x) {
.
.
.
Body of switch statement omitted
}
*dest = val;
}
```


In compiling the function, gcc generates the assembly code that follows for
the initial part of the procedure, with variable x in %rdi

void switch2(short x, short *dest)
x in %rdi
1 switch2:
2 addq $2, %rdi
3 cmpq $8, %rdi
4 ja .L2
5 jmp *.L4(,%rdi,8)


It generates the following code for the jump table:

1 .L4:
2 .quad .L9 # -2
3 .quad .L5 # - 1
4 .quad .L6 # 0
5 .quad .L7 # 1
6 .quad .L2 # 2
7 .quad .L7 # 3
8 .quad .L8 # 4
9 .quad .L2 # 5
10 .quad .L5 # 6

Based on this information, answer the following questions:

What were the values of the case labels in the switch statement?

for the range -2 >= x <= 6:

```c
switch (x) {
 case -2:
    ....
  case -1:
  case 6:
    ....
  case 0:
    ...
  case 1:
  case 3:
    ...
  case 4:
    ...
  default: 
    ...

}
```


What cases had multiple labels in the C code?

case: -1, 6
case 1, 3

## problem 3.31

For a C function switcher with the general structure

```c
void switcher(long a, long b, long c, long *dest)
{
long val;
switch(a) {
case 5: /*CaseA*/
c= b ^ 15;
/* Fall through */
case 0: /*CaseB*/
val = 112 + c;
break;
case 2: /*CaseC*/
case 7: /*CaseD*/
val = (b + c) * 4;
break;
case 4: /*CaseE*/
val = a;
break;
default:
val = b;
}
*dest = val;
}
```

gcc generates the assembly code and jump table shown in Figure 3.24.
Fill in the missing parts of the C code. Except for the ordering of case labels
C and D, there is only one way to fit the different cases into the template.

(a) Code
void switcher(long a, long b, long c, long *dest)
a in %rsi, b in %rdi, c in %rdx, d in %rcx

1 switcher:
2 cmpq $7, %rdi
3 ja .L2
4 jmp *.L4(,%rdi,8)
5 .section .rodata
6 .L7:
7 xorq $15, %rsi
8 movq %rsi, %rdx
9 .L3:
10 leaq 112(%rdx), %rdi
11 jmp .L6
12 .L5:
13 leaq (%rdx,%rsi), %rdi
14 salq $2, %rdi
15 jmp .L6
16 .L2:
17 movq %rsi, %rdi
18 .L6:
19 movq %rdi, (%rcx)
20 ret

(b) Jump table
1 .L4:
2 .quad .L3 # 0
3 .quad .L2 # 1 default
4 .quad .L5 # 2
5 .quad .L2 # 3 default
6 .quad .L6 # 4
7 .quad .L7 # 5
8 .quad .L2 # 6 default
9 .quad .L5 # 7

## problem 3.32

The disassembled code for two functions first and last is shown below, along
with the code for a call of first by function main:

Disassembly of last(long u, long v)
u in %rdi, v in %rsi

1 0000000000400540 <last>:
2 400540: 48 89 f8        mov %rdi,%rax      L1: u
3 400543: 48 0f af c6     imul %rsi,%rax L2:    u*v
4 400547: c3 retq L3:     Return

Disassembly of last(long x)
x in %rdi

5 0000000000400548 <first>:
6 400548: 48 8d 77 01    lea 0x1(%rdi),%rsi  F1:  x+1
7 40054c: 48 83 ef 01    sub $0x1,%rdi       F2:  x-1
8 400550: e8 eb ff ff ff callq 400540 <last> F3: Call last(x-1,x+1)
9 400555: f3 c3          repz retq F4:       Return

10 400560: e8 e3 ff ff ff callq 400548 <first> M1: Call first(10)
11 400565: 48 89 c2 mov %rax,%rdx              M2: Resume

Each of these instructions is given a label, similar to those in Figure 3.27(a).
Starting with the calling of first(10) by main, fill in the following table to trace
instruction execution through to the point where the program returns back to
main.

Instruction           State values (at beginning)
Label PC        Instruction   %rdi %          rsi     %rax     %rsp             *%rsp       Description
M1    0x400560  callq          10              -        -    0x7fffffffe820       —         Call first(10)
F1    0x400548  lea            10              -        -    0x7fffffffe818      0x400565    entry of first
F2    0x40054c  sub            10              11       -    0x7fffffffe818      0x400565    sub x - 1 
F3    0x400550  callq          9               11       -    0x7fffffffe818      0x400565    call last(9,11)
L1    0x400540  mov            9               11       -    0x7fffffffe810      0x400555    entry of last
L2    0x400543  imul           9               11       9    0x7fffffffe810      0x400555    multiply u * v
L3    0x400547  retq           9               11       99   0x7fffffffe810      0x400555    return 99 from last
F4    0x400555  repz retq      9               11       99   0x7fffffffe818      0x400565    return 99 from first
M2    0x400565  mov            9               11       99   0x7fffffffe820      -           Resume

## problem 3.33

A C function procprob has four arguments u, a, v, and b. Each is either a signed
number or a pointer to a signed number, where the numbers have different sizes.
The function has the following body:

```c
*u += a;
*v += b;
return sizeof(a) + sizeof(b);
```

It compiles to the following x86-64 code:

1 procprob:
2 movslq %edi, %rdi
3 addq %rdi, (%rdx)
4 addb %sil, (%rcx)
5 movl $6, %eax
6 ret

Determine a valid ordering and types of the four parameters. There are two
correct answers.

int procprob(int a, short b,  long *u, char *v);

## problem 3.34

Consider a function P, which generates local values, named a0–a8. It then calls
function Q using these generated values as arguments. Gcc produces the following
code for the first part of P:

 long P(long x)
x in %rdi
1 P:
2 pushq %r15
3 pushq %r14
4 pushq %r13
5 pushq %r12
6 pushq %rbp
7 pushq %rbx
8 subq $24, %rsp
9 movq %rdi, %rbx
10 leaq 1(%rdi), %r15
11 leaq 2(%rdi), %r14
12 leaq 3(%rdi), %r13
13 leaq 4(%rdi), %r12
14 leaq 5(%rdi), %rbp
15 leaq 6(%rdi), %rax
16 movq %rax, (%rsp)
17 leaq 7(%rdi), %rdx
18 movq %rdx, 8(%rsp)
19 movl $0, %eax
20 call Q

A) Identify which local values get stored in callee-saved registers.

x is saved into %rbx
x + 1 saved in %r15
x + 2 saved in %r14
x + 3 saved in %r13
x + 4 saved in %r12
x + 5 saved in %rbp

B) Identify which local values get stored on the stack.
x + 6 saved on the stack at %rsp - 24
x + 7 saved on the stack at %rsp - 16

C) Explain why the program could not store all of the local values in callee-
saved registers

Because there are only 6 callee-saved registers

## problem 3.35

For a C function having the general structure

```c
long rfun(unsigned long x) {
if (x == 0)
return 0;
unsigned long nx = x >> 2;
long rv = rfun(nx);
return x + rv;
}
```

gcc generates the following assembly code:
long rfun(unsigned long x)
x in %rdi
1 rfun:
2 pushq %rbx
3 movq %rdi, %rbx
4 movl $0, %eax
5 testq %rdi, %rdi
6 je .L2
7 shrq $2, %rdi
8 call rfun
9 addq %rbx, %rax
10 .L2:
11 popq %rbx
12 ret

A) What value does rfun store in the callee-saved register %rbx?

it stores the value of x.

B) Fill in the missing expressions in the C code shown above.

## problem 3.36

Consider the following declarations:

```c
int P[5];
short Q[2];
int **R[9];
double *S[10];
short *T[2];

```

Fill in the following table describing the element size, the total size, and the
address of element i for each of these arrays.

Array  Element size     Total size   Start address     Element i
P      4                20           xp                xp + 4i
Q      2                4            xq                xq + 2i
R      8                72           xr                xr + 8i
S      8                80           xs                xs + 8i
T      8                16           xt                xt + 8i

## problem 3.37

Suppose xP, the address of short integer array P, and long integer index i are stored
in registers %rdx and %rcx, respectively. For each of the following expressions, give
its type, a formula for its value, and an assembly-code implementation. The result
should be stored in register %rax if it is a pointer and register element %ax if it has
data type short.

Expression        Type      Value            Assembly code
```c
P[1]              short     M[xp + 2]        movw  2(%rdx), %ax
P+3+i             short *   xp + 6 + 2i      leaq  6(%rdx,%rcx,2), %rax
P[i*6-5]          short     M[xp + 12i - 10] movw  -10(%rdx,rcx, 12), %ax
P[2]              short     M[xp + 4]        movw  4(%rdx), %ax
&P[i + 2]         short *   xp + 2i + 4      leaq  4(%rdx, rcx, 2), %rax
```

## problem 3.38

Consider the following source code, where M and N are constants declared with
```c
#define:
long P[M][N];
long Q[N][M];
long sum_element(long i, long j) {
return P[i][j] + Q[j][i];
}
```

In compiling this program, gcc generates the following assembly code:

long sum_element(long i, long j)
i in %rdi, j in %rsi
1 sum_element:
2 leaq 0(,%rdi,8), %rdx
3 subq %rdi, %rdx
4 addq %rsi, %rdx
5 leaq (%rsi,%rsi,4), %rax
6 addq %rax, %rdi
7 movq Q(,%rdi,8), %rax
8 addq P(,%rdx,8), %rax
9 ret

Use your reverse engineering skills to determine the values of M and N based
on this assembly code

M = 5
N = 7

## problem 3.39

Use Equation 3.1 to explain how the computations of the initial values for Aptr,
Bptr, and Bend in the C code of Figure 3.37(b) (lines 3–5) correctly describe their
computations in the assembly code generated for fix_prod_ele (lines 3–5).

Aptr initial value = xa + 4(16 * i)
Bptr initial value =  xb + 4 * k;
BEnd initial value = xb + 4k + 16 * 16

## problem 3.40

The following C code sets the diagonal elements of one of our fixed-size arrays to
val:

```c
/* Set all diagonal elements to val */
void fix_set_diag(fix_matrix A, int val) {
long i;
for(i=0;i<N;i++)
  A[i][i] = val;
}
```

When compiled with optimization level -O1, gcc generates the following
assembly code:

1 fix_set_diag:
void fix_set_diag(fix_matrix A, int val)
A in %rdi, val in %rsi
2 movl $0, %eax
3 .L13:
4 movl %esi, (%rdi,%rax)
5 addq $68, %rax
6 cmpq $1088, %rax
7 jne .L13
8 rep; ret

Create a C code program fix_set_diag_opt that uses optimizations similar
to those in the assembly code, in the same style as the code in Figure 3.37(b). Use
expressions involving the parameter N rather than integer constants, so that your
code will work correctly if N is redefined.

```c
/* Set all diagonal elements to val */
void fix_set_diag(fix_matrix A, int val) {
    int *Aptr = &A[0][0];
    int *AEnd = &A[N][N];
    do {
     *Aptr = val;
     Aptr+= 1 + N;
    }while(Aptr != AEnd);
}
```

## problem 4.41

Consider the following structure declaration:

```c
struct test {
short *p;
struct {
  short x;
  short y;
  }s;
struct test *next;
};

```
This declaration illustrates that one structure can be embedded within another,
just as arrays can be embedded within structures and arrays can be embedded
within arrays.
The following procedure (with some expressions omitted) operates on this
structure:

```c
void st_init(struct test *st) {
st->s.y = ;
st->p = ;
st->next = ;
}
```

A)  What are the offsets (in bytes) of the following fields?
p: 0
s.x: 8
s.y: 10
next: 12

B) How many total bytes does the structure require?

8 + 2 + 2 + 8 = 20 bytes

C) he compiler generates the following assembly code for st_init:

void st_init(struct test *st)
st in %rdi
1 st_init:
2 movl 8(%rdi), %eax
3 movl %eax, 10(%rdi)
4 leaq 10(%rdi), %rax
5 movq %rax, (%rdi)
6 movq %rdi, 12(%rdi)
7 ret

On the basis of this information, fill in the missing expressions in the code
for st_init.

```c
void st_init(struct test *st) {
st->s.y = st->s.x;
st->p = &(st->s.y);
st->next = st;
}
```

## problem 3.42

The following code shows the declaration of a structure of type ACE and the
prototype for a function test:

```c
struct ACE {
short v;
struct ACE *p;
};

short test(struct ACE *ptr)
```

When the code for fun is compiled, gcc generates the following assembly
code:

short test(struct ACE *ptr)
ptr in %rdi
1 test:
2 movl $1, %eax
3 jmp .L2
4 .L3:
5 imulq (%rdi), %rax
6 movq 2(%rdi), %rdi
7 .L2:
8 testq %rdi, %rdi
9 jne .L3
10 rep; ret

A) Use your reverse engineering skills to write C code for test.

```c

short test(struct ACE *ptr){
  short result = 1;

  while(ptr){
    result*= ptr->v;
    ptr = ptr->p;
  }
  return result;
}
```

B) Describe the data structure that this structure implements and the operation
performed by test

The data structure is a linked list and test performs the products of all the element of the linked list.

## problem 3.43

Suppose you are given the job of checking that a C compiler generates the proper
code for structure and union access. You write the following structure declaration:

```c
typedef union {
  struct {
  long u;
  short v;
  char w;
  } t1;
  struct {
  int a[2];
  char *p;
  } t2;
} u_type;
```

You write a series of functions of the form

```c
void get(u_type *up, type *dest) {
*dest = expr;
}
```

ith different access expressions expr and with destination data type type set
according to type associated with expr. You then examine the code generated
when compiling the functions to see if they match your expectations.

Suppose in these functions that up and dest are loaded into registers %rdi and
%rsi, respectively. Fill in the following table with data type type and sequences of
one to three instructions to compute the expression and store the result at dest.

expr           type             Code
up->t1.u       long             movq (%rdi), %rax
                                movq %rax, (%rsi)

up->t1.v       short            movl $0, %eax
                                movw 8(%rdi), %ax
                                movq %rax, (%rsi)

&up->t1.w      * char           addq $10 , %rdi
                                movq %rdi , (%rsi) 

up->t2.a       * int a          movq  %rdi, (%rsi) 

up->t2.a[up->t1.u]  int           movl  (%rdi), %rax
                                movl  (%rdi, %rax, 4), %eax
                                movl  %eax , (%rsi) 


*up->t2.p     char              movl 8(%rdi), %rax
                                movb (rax), %al
                                movb %al, (%rsi) 

## problem 3.44

For each of the following structure declarations, determine the offset of each field,
the total size of the structure, and its alignment requirement for x86-64:

A) struct P1 { short i; int c; int *j; short *d; };

```c

i = 0 ->  c = 2 ->  j = 6 -> d = 14 ->  padding = 22 -> 2;
```

total size 24

B) 
```c

struct P2 { int i[2]; char c[8]; short s[4]; long *j; };
```

i2 = 0 -> c8 = 8 -> s4 = 16 -> j = 24 ->  32

total size 32 

C)
```c

struct P3 { long w[2]; int *c[2] };
```

w2[2] = 0 -> c = 16 -> 32

total size 32 

D) 
```c

struct P4 { char w[16]; char *c[2] };
```

w[16] = 0 -> c = 16 -> 32

total size 32

E)

```c
struct P5 { struct P4 a[2]; struct P1 t };
```

a[2] = 0 -> t = 64 -> 88 

total size 88

## problem 3.45

Answer the following for the structure declaration

```c
struct {
int *a;
float b;
char c;
short d;
long e;
double f;
int g;
char *h;
} rec;
```

A) What are the byte offsets of all the fields in the structure?

a = 0 -> b = 8 -> c = 12 -> padding = 13 -> d = 16 -> e = 18 -> f = 26 -> g = 34 -> padding = 38 -> h = 42 -> 50 -> padding 56

B) What is the total size of the structure?

Total size = 48 bytes

C) Rearrange the fields of the structure to minimize wasted space, and then
show the byte offsets and total size for the rearranged structure.

```c
struct {
int *a;
char *h;
long e;
double f;
float b;
int g;
short d;
char c;
} rec;
```


a = 0 -> h = 8 -> e = 16 -> f = 24 -> b = 32 -> g = 36 -> d = 40 -> c = 42 -> padding -> 48


Total size = 48 bytes

## problem 3.46

Figure 3.41 shows a (low-quality) implementation of a function that reads a line
from standard input, copies the string to newly allocated storage, and returns a
pointer to the result.

Consider the following scenario. Procedure get_line is called with the return
address equal to 0x400776 and register %rbx equal to 0x0123456789ABCDEF.You
type in the string

0123456789012345678901234

The program terminates with a segmentation fault. You run gdb and determine
that the error occurs during the execution of the ret instruction of get_line.

A) Fill in the diagram that follows, indicating as much as you can about the stack
just after executing the instruction at line 3 in the disassembly. Label the
quantities stored on the stack (e.g., “Return address”) on the right, and their
hexadecimal values (if known) within the box. Each box represents 8 bytes.
Indicate the position of %rsp. Recall that the ASCII codes for characters 0–9
are 0x30–0x39.


0123456789012345678901234

00 00 00 00 00 40 00 76  return address
0x0123456789ABCDEF %rbx
-                       
-                       <- buf



B) Modify your diagram to show the effect of the call to gets (line 5).

0x00    00   00   00   00   40  00 34
0x33 0x32 0x31 0x30 0x39 0x38 0x37 0x36
0x35 0x34 0x33 0x32 0x31 0x30 0x39 0x38
0x37 0x36 0x35 0x34 0x33 0x32 0x31 0x30


C) To what address does the program attempt to return?

0x0000000000400034

D) What register(s) have corrupted value(s) when get_line returns?

register %rbx has been corrupted and is now: 
0x33 0x32 0x31 0x30 0x39 0x38 0x37 0x36

E) Besides the potential for buffer overflow, what two other things are wrong
with the code for get_line

- it should have check that the call to malloc does not return a null pointer
- should have been strlen(buf) + 1 for the call to malloc to take into account the string terminator character \00.

## problem 3.47

Running our stack-checking code 10,000 times on a system running Linux ver-
sion 2.6.16, we obtained addresses ranging from a minimum of 0xffffb754 to a
maximum of 0xffffd754.


A) What is the approximate range of addresses?

d - b = 2 * 16 ^ 3 = around 2 ^ 13

B) If we attempted a buffer overrun with a 128-byte nop sled, about how many
attempts would it take to test all starting addresses?

128 bytes = 2 ^ 7

2 ^ 13 - 2 ^ 7 = 2 ^ 6 = 64

## problem 3.48

The functions intlen, len, and iptoa provide a very convoluted way to compute
the number of decimal digits required to represent an integer. We will use this as
a way to study some aspects of the gcc stack protector facility.

```c
int len(char *s) {
return strlen(s);
}

void iptoa(char *s, long *p) {
long val = *p;
sprintf(s, "%ld", val);
}

int intlen(long x) {
long v;
char buf[12];
v=x;
iptoa(buf, &v);
return len(buf);
}
```

The following show portions of the code for intlen, compiled both with and
without stack protector:
(a) Without protector

int intlen(long x)
x in %rdi
1 intlen:
2 subq $40, %rsp
3 movq %rdi, 24(%rsp)
4 leaq 24(%rsp), %rsi
5 movq %rsp, %rdi
6 call iptoa

(b) With protector

int intlen(long x)
x in %rdi
1 intlen:
2 subq $56, %rsp
3 movq %fs:40, %rax
4 movq %rax, 40(%rsp)
5 xorl %eax, %eax
6 movq %rdi, 8(%rsp)
7 leaq 8(%rsp), %rsi
8 leaq 16(%rsp), %rdi
9 call iptoa

A) For both versions: What are the positions in the stack frame for buf, v, and
(when present) the canary value?

For version 1 (without stack detection mechanism):

buf = %rsp - 40
val = %rsp - 16
no canary value

For version 2 (with stack detection mechanism)

canary value = rsp - 16
val = rsp - 48
buf = rsp - 40


B) How does the rearranged ordering of the local variables in the protected
code provide greater security against a buffer overrun attack?

Overriding buf does not override val.

## problem 3.49

A) Explain, in mathematical terms, the logic in the computation of s2 on lines
5–7. Hint: Think about the bit-level representation of−16 and its effect in
the andq instruction of line 6

it's like doing:

%rax = 22 + %rdi * 8

%rsp = %rax - (%rax % 16)

B) Explain, in mathematical terms, the logic in the computation of p on lines
8–10. Hint: You may want to refer to the discussion on division by powers
of 2 in Section 2.3.7.

it like doing:

%rax = (%rsp + 7) / 8

C) For the following values of n and s1, trace the execution of the code to
determine what the resulting values would be for s2, p, e1, and e2


n   s1      s2     p             e1      e2
5 2,065    2017   2024            1      7      
6 2,064    2000   2000            16       0

D) What alignment properties does this code guarantee for the values of s2
and p?

s2 is padded so that p + (n * 8) is aligned on 8.

## problem 3.50

For the following C code, the expressions val1–val4 all map to the program values
i, f, d, and l:

```c
double fcvt2(int *ip, float *fp, double *dp, long l)
{
  int i = *ip; float f = *fp; double d = *dp;
  *ip = (int) val1;
  *fp = (float) val2;
  *dp = (double) val3;
  return (double) val4;
}
```

Determine the mapping, based on the following x86-64 code for the function:

double fcvt2(int *ip, float *fp, double *dp, long l)
ip in %rdi, fp in %rsi, dp in %rdx, l in %rcx
Result returned in %xmm0

fcvt2:
movl (%rdi), %eax
vmovss (%rsi), %xmm0
vcvttsd2si (%rdx), %r8d
movl %r8d, (%rdi)
vcvtsi2ss %eax, %xmm1, %xmm1
vmovss %xmm1, (%rsi)
vcvtsi2sdq %rcx, %xmm1, %xmm1
vmovsd %xmm1, (%rdx)
vunpcklps %xmm0, %xmm0, %xmm0
vcvtps2pd %xmm0, %xmm0
ret

```c
double fcvt2(int *ip, float *fp, double *dp, long l)
{
  int i = *ip; float f = *fp; double d = *dp;
  *ip = (int) d;
  *fp = (float) i;
  *dp = (double) l;
  return (double) f;
}
```

## problem 3.51

The following C function converts an argument of type src_t to a return value of
type dst_t, where these two types are defined using typedef:

```c
dest_t cvt(src_t x)
{
dest_t y = (dest_t) x;
return y;
}
```

For execution on x86-64, assume that argument x is either in %xmm0 or in
the appropriately named portion of register %rdi (i.e., %rdi or %edi). One or two instructions are to be used to perform the type conversion and to copy the value to the appropriately named portion of register %rax (integer result) or %xmm0 (floating-point result). Show the instruction(s), including the source and destination registers.

Tx        Ty       Instructions
long      double   vctsi2sdq  %rdi , %xmm0
double    int      vcttsd2dsi %xmm0 ,%eax
double    float    vctsd2ss %xmm0, %xmm0, %xmm0
long      float    vctsi2ssq %rdi, %xmm0, %xmm0
float     long     vcttss2siq %xmm0, %rax

## problem 3.52

For each of the following function declarations, determine the register assignments
for the arguments:

A) double g1(double a, long b, float c, int d);

%xmm0, %rdi, %xmm1, %esi

B) double g2(int a, double *b, float *c, long d);

%edi, %rsi, %rdx, %rcx 

C) double g3(double *a, double b, int c, float d);

%rdi, %xmm0, %esi, %xmm1

D) double g4(float a, int *b, float c, double d);

%xmm0, %rdi, %xmm1, %xmm2

## problem 3.53

For the following C function, the types of the four arguments are defined by
typedef:

```c
double funct1(arg1_t p, arg2_t q, arg3_t r, arg4_t s)
{
return p/(q+r) - s;
}
```

When compiled, gcc generates the following code:

double funct1(arg1_t p, arg2_t q, arg3_t r, arg4_t s)
vcvtsi2ssq %rsi, %xmm2, %xmm2 # convert quad word (second normal register) to float
vaddss %xmm0, %xmm2, %xmm0 # add float + converted quad word to float
vcvtsi2ss %edi, %xmm2, %xmm2 # convert int (first normal register) to float
vdivss %xmm0, %xmm2, %xmm0  #  converted int to float /  float
vunpcklps %xmm0, %xmm0, %xmm0
vcvtps2pd %xmm0, %xmm0 # convert result to double
vsubsd %xmm1, %xmm0, %xmm0 # result / double (second floating point argument)
ret

Determine the possible combinations of types of the four arguments (there
may be more than one).

there are:
%edi = int
%rsi = long
%xmm0 = float
%xmm1 = double

combinations:

double funct1(int p, long  q, float r, double s)
double funct1(int p, float  q, long r, double s)

## problem 3.54

Function funct2 has the following prototype:

double funct2(double w, int x, float y, long z);

Gcc generates the following code for the function:

double funct2(double w, int x, float y, long z)
w in %xmm0, x in %edi, y in %xmm1, z in %rsi
funct2:
vcvtsi2ss %edi, %xmm2, %xmm2
vmulss %xmm1, %xmm2, %xmm1
vunpcklps   %xmm1, %xmm1, %xmm1
vcvtps2pd   %xmm1, %xmm2
vcvtsi2sdq  %rsi, %xmm1, %xmm1
vdivsd      %xmm1, %xmm0, %xmm0
vsubsd      %xmm0, %xmm2, %xmm0
ret

Write a C version of funct2.

```c
double funct2(double w, int x, float y, long z){
  return (x * y) - (w / z);
}
```

## problem 3.55

Show how the numbers declared at label .LC3 encode the number 32.0.

Low order bytes = 0x0
High order bytes = 0x40400000

0x404 = 1028

exp = 1028 - 1023  = 5

2^5 = 32

## problem 3.56

Consider the following C function, where EXPR is a macro defined with #define:

```c
double simplefun(double x) {
return EXPR(x);
}
```

Below, we show the AVX2 code generated for different definitions of EXPR,
where value x is held in %xmm0. All of them correspond to some useful operation on
floating-point values. Identify what the operations are. Your answers will require
you to understand the bit patterns of the constant words being retrieved from
memory.

A) 1 vmovsd .LC1(%rip), %xmm1
2 vandpd %xmm1, %xmm0, %xmm0
3 .LC1:
4 .long 4294967295
5 .long 2147483647
6 .long 0
7 .long 0

The goal is basically to do an and with 0x7fffffffffffffff to make the double positive.


```c
double simplefun(double x) {
return x & 0x7fffffffffffffff;
}

```


B) vxorpd %xmm0, %xmm0, %xmm0

The goal is to return  zero by doing a xor of x with itself.


```c
double simplefun(double x) {
return x ^ x;
}

```

C. 
1 vmovsd .LC2(%rip), %xmm1
2 vxorpd %xmm1, %xmm0, %xmm0 
3.LC2:
4 .long 0
5 .long -2147483648
6 .long 0
7 .long 0

The goal is basically to do a xor with 0x8000000000000000 to inverse the sign of x.


```c
double simplefun(double x) {
return x ^ 0x8000000000000000;
}

```
