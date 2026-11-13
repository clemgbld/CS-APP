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


