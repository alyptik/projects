# Disassembly of file: asm
# Fri Dec 30 23:48:23 2016
# Mode: 64 bits
# Syntax: GAS(Intel)
# Instruction set: 8086, x64

# Note: Uses Intel syntax with destination operand first. Remember to
# put syntax directives in the beginning and end of inline assembly:
.intel_syntax noprefix 

.global _end
.global _edata
.global __bss_start
.global _start

.equ    len2, 0x00000002                                # 2
.equ    len, 0x00000002                                 # 2
.equ    len3, 0x00000010                                # 16


.SECTION .text  # "ax", @progbits                       # section number 1, code
        .ALIGN  1

_start:                                                 # Function
        .type   _start, @function
        mov     edx, 14                                 # 004000B0 _ BA, 0000000E
        mov     ecx, offset msg                         # 004000B5 _ B9, 006000E8(d)
        mov     ebx, 1                                  # 004000BA _ BB, 00000001
        mov     eax, 4                                  # 004000BF _ B8, 00000004
        int     -128                                    # 004000C4 _ CD, 80
        mov     edx, 14                                 # 004000C6 _ BA, 0000000E
        mov     ecx, offset foo                         # 004000CB _ B9, 006000F6(d)
        mov     ebx, 1                                  # 004000D0 _ BB, 00000001
        mov     eax, 4                                  # 004000D5 _ B8, 00000004
        int     -128                                    # 004000DA _ CD, 80
        mov     ebx, 0                                  # 004000DC _ BB, 00000000
        mov     eax, 1                                  # 004000E1 _ B8, 00000001
# Note: Function does not end with ret or jmp
        int     -128                                    # 004000E6 _ CD, 80
        .size   _start, . - _start                      # End of function is probably here


.SECTION .data  # "aw", @progbits                       # section number 2, data
        .ALIGN  1

msg:                                                    # byte
        .byte  0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x2C, 0x20, 0x77# 006000E8 _ Hello, w
        .byte  0x6F, 0x72, 0x6C, 0x64, 0x21, 0x0A       # 006000F0 _ orld!.

foo:                                                    # byte
        .byte  0x31, 0x0A                               # 006000F6 _ 1.


# Return to AT&T syntax with destination operand last:
.att_syntax prefix 
