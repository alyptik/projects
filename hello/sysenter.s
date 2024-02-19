.data
msg:
    .ascii "Hello World!\n"
    len = . - msg

.text
.global _start
_start:
    pushl  %ebp
    movl   %esp, %ebp
# Write the string to stdout
    movl   $len, %edx
    movl   $msg, %ecx
    movl   $1, %ebx
    movl   $4, %eax
# Setting the stack for the systenter
    pushl  $sysenter_ret
    pushl  %ecx
    pushl  %edx
    pushl  %ebp
    movl   %esp,%ebp
    sysenter
# and exit
sysenter_ret:
    movl   $0, %ebx
    movl   $1, %eax
# Setting the stack for the systenter
    pushl  $sysenter_ret # Who cares, this is an exit !
    pushl  %ecx
    pushl  %edx
    pushl  %ebp
    movl   %esp,%ebp
    sysenter

