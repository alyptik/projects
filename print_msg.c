/*
 * From: https://stackoverflow.com/questions/13901261/calling-assembly-function-from-c
 *
 * Not sure if you have solved this or not, but here is how I have done this.
 * When compiling make sure to add both files:
 *
 * $ gcc -no-pie print_msg.c print_msg.s -o print_msg
 *
 * To run the assembler file on its own:
 *
 * $ as print_msg.s -o print_msg.o
 *
 * followed by:
 *
 * $ ld print_msg.o -e print -o print_msg
 *
 * Note that this is not required if you only want to run it from your C file.
 *
 * The assembler file: print_msg.s
 *
 * # A program to be called from a C program
 * # Declaring data that doesn't change
 * .section .data
 *     string: .ascii  "Hello from assembler\n"
 *     length: .quad   . - string
 *
 * # The actual code
 * .section .text
 * .global print
 * .type print, @function              #<-Important
 *
 * print:
 *     mov     $0x1,%rax               # Move 1(write) into rax
 *     mov     $0x1,%rdi               # Move 1(fd stdOut) into rdi.
 *     mov     $string,%rsi            # Move the _location_ of the string into rsi
 *     mov     length,%rdx             # Move the _length_ of the string into rdx
 *     syscall                         # Call the kernel
 *
 *     mov     %rax,%rdi               # Move the number of bytes written to rdi
 *     mov     $0x3c,%rax              # Move 60(sys_exit) into rax
 *     syscall                         # Call the kernel
 */

extern void print(void);

int main(void)
{
    print();
    return 0;
}
