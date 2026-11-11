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
