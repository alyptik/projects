.text				    # section declaration
			            # we must export the entry point to the ELF linker or
	.global _start		    # loader. They conventionally recognize _start as their
			            # entry point. Use ld -e foo to override the default.
_start:

	# Write the string to stdout
	movq  $len, %rdx
	movq  $msg, %rsi
	movq  $1, %rdi
	movq  $1, %rax
	syscall			    # write our string to stdout

	movl    $len,%edx           # third argument: message length
	movl    $msg,%ecx           # second argument: pointer to message to write
	movl    $1,%ebx             # first argument: file handle (stdout)
	movl    $4,%eax             # system call number (sys_write)
	int     $0x80               # call kernel

	movl    $len,%edx           # third argument: message length
	movl    $foo,%ecx           # second argument: pointer to message to write
	movl    $1,%ebx             # first argument: file handle (stdout)
	movl    $4,%eax             # system call number (sys_write)
	int     $0x80               # call kernel

	#movq  $0, %rdi
	#movq  $60, %rax
	#syscall

	# Write the string to stdout
	movl  $len, %edx
	movl  $msg, %ecx
	movl  $1, %ebx
	movl  $4, %eax
	sub $12, %esp
	mov %esp, %ebp
	int     $0x80               # call kernel
	#sysenter

	movl    $0,%ebx             # first argument: exit code
	movl    $1,%eax             # system call number (sys_exit)
	int     $0x80               # call kernel



.data                           # section declaration

msg:
	.ascii    "Hello, world!\n"   # our dear string
	len = . - msg                 # length of our dear string
	foo:
	.byte	  0x31,0x0a
	len = . - foo
	len2 = . - foo
	len3 = . - msg
#final:
#	movl  $0, %ebx
#	movl  $1, %eax
#
#	sub $12, %esp
#	mov %esp, %ebp
#
#	sysenter
