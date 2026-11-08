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

