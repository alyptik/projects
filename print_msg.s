# A program to be called from a C program
# Declaring data that doesn't change
.section .data
    string: .ascii  "Hello from assembler!\n"
    length: .quad   . - string

# The actual code
.section .text
.global print
# Important
.type print, @function

print:
    # Move 1(write) into rax
    mov     $0x1, %rax
    # Move 1(fd stdOut) into rdi.
    mov     $0x1, %rdi
    # Move the _location_ of the string into rsi
    mov     $string, %rsi
    # Move the _length_ of the string into rdx
    mov     length, %rdx
    # Call the kernel
    syscall

    # Move the number of bytes written to rdi
    mov     %rax, %rdi
    # Move 60(sys_exit) into rax
    mov     $0x3c, %rax

    # Call the kernel
    syscall

