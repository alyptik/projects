
.text
        .global _start
        .global _strlen
        .global _strlen_next
        .global _strlen_null

        _start:
                movl    $msg, %edi
                call    _strlen

                movl    %eax, %edx # third argument: message length.
                movl    $msg, %ecx # second argument: pointer to message to write.
                movl    $1,%ebx # first argument: file handle (stdout).
                movl    $4,%eax # system call number (sys_write).
                int     $0x80     # call kernel.

                # and exit.
                movl    $0,%ebx   # first syscall argument: exit code.
                movl    $1,%eax # system call number (sys_exit).
                #syscall
                #sysenter
                int     $0x80     # call kernel.

        _strlen:
                push	%ecx                    # save and clear out counter
                xorl    %ecx,%ecx

        _strlen_next:

                cmpb    $0,(%edi)      # null byte yet?
                jz      _strlen_null    # yes, get out

                incl    %ecx                    # char is ok, count it
                incl    %edi                    # move to next char
                jmp     _strlen_next    # process again

        _strlen_null:

                movl    %ecx,%eax               # ecx = the length (put in eax)
                popl    %ecx                    # restore ecx
                ret                     # get out

.data
        msg:    .asciz  "Hello, world!\n"
        # len:  equ     $ - msg
        # times 510-($-$$)      db      0

