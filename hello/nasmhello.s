
section .text
	global _start
	global _strlen
	global _strlen_next
	global _strlen_null

	_start:
		mov	edi, msg
		call	_strlen

		mov  	edx,eax	; third argument: message length.
		mov  	ecx,msg	; second argument: pointer to message to write.
		mov  	ebx,1  	; first argument: file handle (stdout).
		mov  	eax,4  	; system call number (sys_write).
		int  	0x80	  ; call kernel.

  		; and exit.
		mov	ebx,0	  ; first syscall argument: exit code.
		mov  	eax,1  	; system call number (sys_exit).
		;syscall
		;sysenter
		int  	0x80	  ; call kernel.

	_strlen:
		push	ecx      		; save and clear out counter
		xor	ecx, ecx

	_strlen_next:

		cmp	[edi], byte 0  ; null byte yet?
		jz 	_strlen_null	; yes, get out

		inc	ecx      		; char is ok, count it
		inc	edi      		; move to next char
		jmp	_strlen_next	; process again

	_strlen_null:

		mov	eax, ecx 		; ecx = the length (put in eax)
		pop	ecx      		; restore ecx
		ret            		; get out

section .data
	msg:  	db	'Hello, world!\n', 0
	; len:	equ	$ - msg
	; times	510-($-$$)	db	0

; vim: filetype=nasm
