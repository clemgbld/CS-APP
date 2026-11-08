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
