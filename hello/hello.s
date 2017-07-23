# mark_description "Intel(R) C Intel(R) 64 Compiler for applications running on Intel(R) 64, Version 17.0.4.196 Build 20170411";
# mark_description "-lcrypt -S -o hello.s";
	.file "hello.c"
	.text
..TXTST0:
# -- Begin  main
	.text
# mark_begin;
       .align    16,0x90
	.globl main
# --- main(int, char **)
main:
# parameter 1: %edi
# parameter 2: %rsi
..B1.1:                         # Preds ..B1.0
                                # Execution count [1.00e+00]
	.cfi_startproc
..___tag_value_main.1:
..L2:
                                                          #33.33
        pushq     %rbp                                          #33.33
	.cfi_def_cfa_offset 16
        movq      %rsp, %rbp                                    #33.33
	.cfi_def_cfa 6, 16
	.cfi_offset 6, -16
        andq      $-128, %rsp                                   #33.33
        pushq     %r13                                          #33.33
        pushq     %r14                                          #33.33
        pushq     %r15                                          #33.33
        pushq     %rbx                                          #33.33
        subq      $96, %rsp                                     #33.33
	.cfi_escape 0x10, 0x03, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0xe0, 0xff, 0xff, 0xff, 0x22
	.cfi_escape 0x10, 0x0d, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0xf8, 0xff, 0xff, 0xff, 0x22
	.cfi_escape 0x10, 0x0e, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0xf0, 0xff, 0xff, 0xff, 0x22
	.cfi_escape 0x10, 0x0f, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0xe8, 0xff, 0xff, 0xff, 0x22
        movq      %rsi, %r15                                    #33.33
        movl      %edi, %r14d                                   #33.33
        xorl      %esi, %esi                                    #33.33
        movl      $3, %edi                                      #33.33
        call      __intel_new_feature_proc_init                 #33.33
                                # LOE r12 r15 r14d
..B1.66:                        # Preds ..B1.1
                                # Execution count [1.00e+00]
        stmxcsr   (%rsp)                                        #33.33
        movl      $.L_2__STRING.0, %edi                         #36.2
        lea       40(%rsp), %rsi                                #36.2
        orl       $32832, (%rsp)                                #33.33
        xorl      %eax, %eax                                    #36.2
        ldmxcsr   (%rsp)                                        #33.33
        movslq    %r14d, %r14                                   #33.33
#       scanf(const char *__restrict__, ...)
        call      scanf                                         #36.2
                                # LOE r12 r14 r15
..B1.2:                         # Preds ..B1.66
                                # Execution count [1.00e+00]
        movq      40(%rsp), %rbx                                #37.92
        lea       48(%rsp), %rdi                                #37.86
        movq      %rbx, %rsi                                    #37.86
        call      __ktoq                                        #37.86
                                # LOE rbx r12 r14 r15
..B1.67:                        # Preds ..B1.2
                                # Execution count [1.00e+00]
        movq      56(%rsp), %r9                                 #37.86
        movl      $16383, %r8d                                  #37.86
        sarq      $48, %r9                                      #37.86
        movq      $-1, %rdx                                     #37.2
        subq      %r8, %r9                                      #37.86
        testq     %rbx, %rbx                                    #37.2
        movl      $.L_2__STRING.1, %edi                         #37.2
        cmovne    %r9, %rdx                                     #37.2
        movq      %rbx, %rsi                                    #37.2
        movq      $-1, %rcx                                     #37.2
        xorl      %eax, %eax                                    #37.2
..___tag_value_main.10:
#       printf(const char *__restrict__, ...)
        call      printf                                        #37.2
..___tag_value_main.11:
                                # LOE r12 r14 r15
..B1.3:                         # Preds ..B1.67
                                # Execution count [1.00e+00]
        fldt      .L_2il0floatpacket.0(%rip)                    #43.17
        addq      $-16, %rsp                                    #43.17
        fstpt     (%rsp)                                        #43.17
        call      log2l                                         #43.17
                                # LOE r12 r14 r15 f1
..B1.69:                        # Preds ..B1.3
                                # Execution count [1.00e+00]
        movl      $.L_2__STRING.2, %edi                         #38.2
        movl      $255, %esi                                    #38.2
        movl      $65535, %edx                                  #38.2
        movq      $0x0ffffffff, %rcx                            #38.2
        movq      $-1, %r8                                      #38.2
        xorl      %eax, %eax                                    #38.2
        fstpt     (%rsp)                                        #38.2
..___tag_value_main.12:
#       printf(const char *__restrict__, ...)
        call      printf                                        #38.2
..___tag_value_main.13:
                                # LOE r12 r14 r15
..B1.68:                        # Preds ..B1.69
                                # Execution count [1.00e+00]
        addq      $16, %rsp                                     #38.2
                                # LOE r12 r14 r15
..B1.4:                         # Preds ..B1.68
                                # Execution count [1.00e+00]
        movl      $-1, %esi                                     #48.2
        movl      $.L_2__STRING.4, %edi                         #48.2
        movl      %esi, %edx                                    #48.2
        movl      %esi, %ecx                                    #48.2
        xorl      %eax, %eax                                    #48.2
..___tag_value_main.14:
#       printf(const char *__restrict__, ...)
        call      printf                                        #48.2
..___tag_value_main.15:
                                # LOE r12 r14 r15
..B1.5:                         # Preds ..B1.4
                                # Execution count [1.00e+00]
        movl      $131232, %edi                                 #50.28
#       malloc(size_t)
        call      malloc                                        #50.28
                                # LOE rax r12 r14 r15
..B1.70:                        # Preds ..B1.5
                                # Execution count [1.00e+00]
        movq      %rax, %r13                                    #50.28
                                # LOE r12 r13 r14 r15
..B1.6:                         # Preds ..B1.70
                                # Execution count [1.00e+00]
        movl      $.L_2__STRING.3, %edi                         #53.9
        movq      %rdi, %rsi                                    #53.9
..___tag_value_main.16:
#       crypt(const char *, const char *)
        call      crypt                                         #53.9
..___tag_value_main.17:
                                # LOE rax r12 r13 r14 r15
..B1.71:                        # Preds ..B1.6
                                # Execution count [1.00e+00]
        movq      %rax, %rbx                                    #53.9
                                # LOE rbx r12 r13 r14 r15
..B1.7:                         # Preds ..B1.71
                                # Execution count [1.00e+00]
        movl      $.L_2__STRING.3, %edi                         #54.10
        movq      %r13, %rdx                                    #54.10
        movq      %rdi, %rsi                                    #54.10
..___tag_value_main.18:
#       crypt_r(const char *, const char *, struct crypt_data *__restrict__)
        call      crypt_r                                       #54.10
..___tag_value_main.19:
                                # LOE rax rbx r12 r14 r15
..B1.8:                         # Preds ..B1.7
                                # Execution count [1.00e+00]
        movl      $.L_2__STRING.5, %edi                         #55.2
        movq      %rbx, %rsi                                    #55.2
        movq      %rax, %rdx                                    #55.2
        xorl      %eax, %eax                                    #55.2
..___tag_value_main.20:
#       printf(const char *__restrict__, ...)
        call      printf                                        #55.2
..___tag_value_main.21:
                                # LOE r12 r14 r15
..B1.9:                         # Preds ..B1.8
                                # Execution count [1.00e+00]
        movups    hello.1169.0.0.4(%rip), %xmm0                 #57.17
        movups    %xmm0, (%rsp)                                 #57.17
        movl      16+hello.1169.0.0.4(%rip), %eax               #57.17
        movl      %eax, 16(%rsp)                                #57.17
                                # LOE r12 r14 r15
..B1.10:                        # Preds ..B1.9
                                # Execution count [1.00e+00]
        movl      $il0_peep_printf_format_0, %edi               #71.3
        movb      $108, 5(%rsp)                                 #58.2
        call      puts                                          #71.3
                                # LOE r12 r14 r15
..B1.11:                        # Preds ..B1.10
                                # Execution count [1.00e+00]
        cmpq      $2, %r14                                      #75.13
        jl        ..B1.14       # Prob 50%                      #75.13
                                # LOE r12 r14 r15
..B1.12:                        # Preds ..B1.11
                                # Execution count [5.00e-01]
        movq      8(%r15), %rdi                                 #78.11
        call      atol                                          #78.11
                                # LOE rax r12 r14 r15
..B1.13:                        # Preds ..B1.12
                                # Execution count [5.00e-01]
        movl      %eax, %edx                                    #78.11
        cmpl      $1, %edx                                      #79.2
        jne       ..B1.27       # Prob 50%                      #79.2
                                # LOE r12 r14 r15 edx
..B1.14:                        # Preds ..B1.11 ..B1.13
                                # Execution count [4.50e-01]
        movsd     .L_2il0floatpacket.1(%rip), %xmm0             #80.6
        movl      $.L_2__STRING.8, %edi                         #80.6
        movsd     .L_2il0floatpacket.4(%rip), %xmm2             #80.6
        movaps    %xmm0, %xmm1                                  #80.6
        movaps    %xmm2, %xmm3                                  #80.6
        movl      $4, %eax                                      #80.6
..___tag_value_main.22:
#       printf(const char *__restrict__, ...)
        call      printf                                        #80.6
..___tag_value_main.23:
                                # LOE r12 r14 r15
..B1.15:                        # Preds ..B1.27 ..B1.63 ..B1.14
                                # Execution count [1.00e+00]
        movl      var.1169.0.4(%rip), %esi                      #83.27
        movl      $.L_2__STRING.9, %edi                         #83.2
        movl      $var.1169.0.4, %edx                           #83.2
        movl      %esi, %ecx                                    #83.2
        movl      $-2, %r8d                                     #83.2
        xorl      %eax, %eax                                    #83.2
..___tag_value_main.24:
#       printf(const char *__restrict__, ...)
        call      printf                                        #83.2
..___tag_value_main.25:
                                # LOE r12 r14 r15
..B1.16:                        # Preds ..B1.15
                                # Execution count [1.00e+00]
        movl      $.L_2__STRING.10, %edi                        #84.2
        movl      $1, %esi                                      #84.2
        xorl      %eax, %eax                                    #84.2
..___tag_value_main.26:
#       printf(const char *__restrict__, ...)
        call      printf                                        #84.2
..___tag_value_main.27:
                                # LOE r12 r14 r15
..B1.17:                        # Preds ..B1.16
                                # Execution count [1.00e+00]
#       fork(void)
        call      fork                                          #86.15
                                # LOE r12 r14 r15
..B1.18:                        # Preds ..B1.17
                                # Execution count [1.00e+00]
        movl      $.L_2__STRING.12, %edi                        #88.2
        call      puts                                          #88.2
                                # LOE r12 r14 r15
..B1.19:                        # Preds ..B1.18
                                # Execution count [1.00e+00]
        movl      $.L_2__STRING.13, %edi                        #89.2
        lea       (%rsp), %rsi                                  #89.2
        xorl      %eax, %eax                                    #89.2
        movsbl    6(%rsi), %edx                                 #89.2
..___tag_value_main.28:
#       printf(const char *__restrict__, ...)
        call      printf                                        #89.2
..___tag_value_main.29:
                                # LOE r12 r14 r15
..B1.20:                        # Preds ..B1.19
                                # Execution count [1.00e+00]
        xorl      %ebx, %ebx                                    #90.7
        testq     %r14, %r14                                    #90.18
        jle       ..B1.25       # Prob 10%                      #90.18
                                # LOE rbx r12 r14 r15
..B1.22:                        # Preds ..B1.20 ..B1.23
                                # Execution count [5.00e+00]
        movq      (%r15,%rbx,8), %rdi                           #91.3
        call      puts                                          #91.3
                                # LOE rbx r12 r14 r15
..B1.23:                        # Preds ..B1.22
                                # Execution count [5.00e+00]
        incq      %rbx                                          #90.24
        cmpq      %r14, %rbx                                    #90.18
        jl        ..B1.22       # Prob 82%                      #90.18
                                # LOE rbx r12 r14 r15
..B1.25:                        # Preds ..B1.23 ..B1.20
                                # Execution count [1.00e+00]
        movl      $.L_2__STRING.14, %edi                        #92.2
        movl      $.L_2__STRING.15, %esi                        #92.2
        xorl      %eax, %eax                                    #92.2
..___tag_value_main.30:
#       printf(const char *__restrict__, ...)
        call      printf                                        #92.2
..___tag_value_main.31:
                                # LOE r12
..B1.26:                        # Preds ..B1.25
                                # Execution count [1.00e+00]
        xorl      %eax, %eax                                    #93.9
        addq      $96, %rsp                                     #93.9
	.cfi_restore 3
        popq      %rbx                                          #93.9
	.cfi_restore 15
        popq      %r15                                          #93.9
	.cfi_restore 14
        popq      %r14                                          #93.9
	.cfi_restore 13
        popq      %r13                                          #93.9
        movq      %rbp, %rsp                                    #93.9
        popq      %rbp                                          #93.9
	.cfi_def_cfa 7, 8
	.cfi_restore 6
        ret                                                     #93.9
	.cfi_def_cfa 6, 16
	.cfi_escape 0x10, 0x03, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0xe0, 0xff, 0xff, 0xff, 0x22
	.cfi_offset 6, -16
	.cfi_escape 0x10, 0x0d, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0xf8, 0xff, 0xff, 0xff, 0x22
	.cfi_escape 0x10, 0x0e, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0xf0, 0xff, 0xff, 0xff, 0x22
	.cfi_escape 0x10, 0x0f, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0xe8, 0xff, 0xff, 0xff, 0x22
                                # LOE
..B1.27:                        # Preds ..B1.13
                                # Execution count [2.50e-01]
        jl        ..B1.15       # Prob 9%                       #79.18
                                # LOE r12 r14 r15 edx
..B1.28:                        # Preds ..B1.27
                                # Execution count [0.00e+00]
        movsd     .L_2il0floatpacket.4(%rip), %xmm6             #80.54
        xorl      %eax, %eax                                    #80.54
        movaps    %xmm6, %xmm3                                  #80.72
        movaps    %xmm6, %xmm2                                  #80.54
        movaps    %xmm3, %xmm5                                  #80.72
        movups    .L_2il0floatpacket.2(%rip), %xmm4             #80.72
        xorl      %r13d, %r13d                                  #80.54
        movl      $.L_2__STRING.8, %ebx                         #80.6
        movq      %r15, 24(%rsp)                                #80.6[spill]
        movl      %eax, %r15d                                   #80.6
        movq      %r12, 32(%rsp)                                #80.6[spill]
	.cfi_escape 0x10, 0x0c, 0x0e, 0x38, 0x1c, 0x0d, 0x80, 0xff, 0xff, 0xff, 0x1a, 0x0d, 0xa0, 0xff, 0xff, 0xff, 0x22
        movl      %edx, %r12d                                   #80.6
                                # LOE rbx r14 r12d r13d r15d xmm2 xmm3 xmm4 xmm5
..B1.29:                        # Preds ..B1.55 ..B1.57 ..B1.28 ..B1.53 ..B1.59
                                #      
                                # Execution count [2.50e+00]
        movsd     .L_2il0floatpacket.1(%rip), %xmm0             #80.6
        movq      %rbx, %rdi                                    #80.6
        movaps    %xmm0, %xmm1                                  #80.6
        movl      $4, %eax                                      #80.6
..___tag_value_main.45:
#       printf(const char *__restrict__, ...)
        call      printf                                        #80.6
..___tag_value_main.46:
                                # LOE rbx r14 r12d r13d r15d
..B1.30:                        # Preds ..B1.29
                                # Execution count [2.50e+00]
        incl      %r15d                                         #79.25
        movups    .L_2il0floatpacket.2(%rip), %xmm4             #
        movsd     .L_2il0floatpacket.4(%rip), %xmm5             #
        cmpl      %r12d, %r15d                                  #79.2
        jae       ..B1.63       # Prob 18%                      #79.2
                                # LOE rbx r14 r12d r13d r15d xmm4 xmm5
..B1.31:                        # Preds ..B1.30
                                # Execution count [2.05e+00]
        pxor      %xmm0, %xmm0                                  #80.67
        movaps    %xmm5, %xmm2                                  #80.54
        cvtsi2sd  %r15d, %xmm0                                  #80.67
        cvttsd2si %xmm0, %eax                                   #80.54
        cltd                                                    #80.54
        movl      %eax, %ecx                                    #80.54
        xorl      %edx, %ecx                                    #80.54
        subl      %edx, %ecx                                    #80.54
        testl     %ecx, %ecx                                    #80.54
        jle       ..B1.57       # Prob 50%                      #80.54
                                # LOE rbx r14 eax r12d r13d r15d xmm2 xmm4 xmm5
..B1.32:                        # Preds ..B1.31
                                # Execution count [2.25e+00]
        cltd                                                    #80.54
        movl      %eax, %r8d                                    #80.54
        movaps    %xmm5, %xmm2                                  #80.54
        xorl      %edx, %r8d                                    #80.54
        subl      %edx, %r8d                                    #80.54
        cmpl      $8, %r8d                                      #80.54
        jl        ..B1.62       # Prob 10%                      #80.54
                                # LOE rbx r14 eax r8d r12d r13d r15d xmm2 xmm4 xmm5
..B1.33:                        # Preds ..B1.32
                                # Execution count [2.25e+00]
        movl      %r8d, %esi                                    #80.54
        movl      %r13d, %ecx                                   #80.54
        movups    .L_2il0floatpacket.3(%rip), %xmm0             #80.54
        movaps    %xmm4, %xmm2                                  #80.54
        andl      $-8, %esi                                     #80.54
                                # LOE rbx r14 eax ecx esi r8d r12d r13d r15d xmm0 xmm2 xmm4 xmm5
..B1.34:                        # Preds ..B1.34 ..B1.33
                                # Execution count [1.25e+01]
        mulpd     %xmm0, %xmm2                                  #80.54
        mulpd     %xmm0, %xmm2                                  #80.54
        mulpd     %xmm0, %xmm2                                  #80.54
        addl      $8, %ecx                                      #80.54
        mulpd     %xmm0, %xmm2                                  #80.54
        cmpl      %esi, %ecx                                    #80.54
        jb        ..B1.34       # Prob 82%                      #80.54
                                # LOE rbx r14 eax ecx esi r8d r12d r13d r15d xmm0 xmm2 xmm4 xmm5
..B1.35:                        # Preds ..B1.34
                                # Execution count [2.25e+00]
        movaps    %xmm2, %xmm0                                  #80.54
        unpckhpd  %xmm2, %xmm0                                  #80.54
        mulsd     %xmm0, %xmm2                                  #80.54
                                # LOE rbx r14 eax esi r8d r12d r13d r15d xmm2 xmm4 xmm5
..B1.36:                        # Preds ..B1.35 ..B1.62
                                # Execution count [2.50e+00]
        cmpl      %r8d, %esi                                    #80.54
        jae       ..B1.40       # Prob 10%                      #80.54
                                # LOE rbx r14 eax esi r8d r12d r13d r15d xmm2 xmm4 xmm5
..B1.37:                        # Preds ..B1.36
                                # Execution count [2.25e+00]
        movsd     .L_2il0floatpacket.1(%rip), %xmm0             #
                                # LOE rbx r14 eax esi r8d r12d r13d r15d xmm0 xmm2 xmm4 xmm5
..B1.38:                        # Preds ..B1.38 ..B1.37
                                # Execution count [1.25e+01]
        incl      %esi                                          #80.54
        mulsd     %xmm0, %xmm2                                  #80.54
        cmpl      %r8d, %esi                                    #80.54
        jb        ..B1.38       # Prob 82%                      #80.54
                                # LOE rbx r14 eax esi r8d r12d r13d r15d xmm0 xmm2 xmm4 xmm5
..B1.40:                        # Preds ..B1.38 ..B1.36
                                # Execution count [1.25e+00]
        movaps    %xmm5, %xmm3                                  #80.72
        testl     %r15d, %r15d                                  #80.54
        jns       ..B1.49       # Prob 50%                      #80.54
                                # LOE rbx r14 eax r12d r13d r15d xmm2 xmm3 xmm4 xmm5
..B1.41:                        # Preds ..B1.40
                                # Execution count [6.25e-01]
        cltd                                                    #80.54
        xorl      %edx, %eax                                    #80.54
        movaps    %xmm2, %xmm0                                  #80.54
        subl      %edx, %eax                                    #80.54
        movsd     .L_2il0floatpacket.4(%rip), %xmm2             #80.54
        divsd     %xmm0, %xmm2                                  #80.54
        cmpl      $8, %eax                                      #80.72
        jl        ..B1.60       # Prob 10%                      #80.72
                                # LOE rbx r14 eax r12d r13d r15d xmm2 xmm3 xmm4 xmm5
..B1.42:                        # Preds ..B1.41
                                # Execution count [2.25e+00]
        movl      %eax, %esi                                    #80.72
        movl      %r13d, %ecx                                   #80.72
        movups    .L_2il0floatpacket.3(%rip), %xmm0             #80.72
        movaps    %xmm4, %xmm3                                  #80.72
        andl      $-8, %esi                                     #80.72
                                # LOE rbx r14 eax ecx esi r12d r13d r15d xmm0 xmm2 xmm3 xmm4 xmm5
..B1.43:                        # Preds ..B1.43 ..B1.42
                                # Execution count [1.25e+01]
        mulpd     %xmm0, %xmm3                                  #80.72
        mulpd     %xmm0, %xmm3                                  #80.72
        mulpd     %xmm0, %xmm3                                  #80.72
        addl      $8, %ecx                                      #80.72
        mulpd     %xmm0, %xmm3                                  #80.72
        cmpl      %esi, %ecx                                    #80.72
        jb        ..B1.43       # Prob 82%                      #80.72
                                # LOE rbx r14 eax ecx esi r12d r13d r15d xmm0 xmm2 xmm3 xmm4 xmm5
..B1.44:                        # Preds ..B1.43
                                # Execution count [2.25e+00]
        movaps    %xmm3, %xmm0                                  #80.72
        unpckhpd  %xmm3, %xmm0                                  #80.72
        mulsd     %xmm0, %xmm3                                  #80.72
                                # LOE rbx r14 eax esi r12d r13d r15d xmm2 xmm3 xmm4 xmm5
..B1.45:                        # Preds ..B1.44 ..B1.60
                                # Execution count [2.50e+00]
        cmpl      %eax, %esi                                    #80.72
        jae       ..B1.59       # Prob 10%                      #80.72
                                # LOE rbx r14 eax esi r12d r13d r15d xmm2 xmm3 xmm4 xmm5
..B1.46:                        # Preds ..B1.45
                                # Execution count [2.25e+00]
        movsd     .L_2il0floatpacket.1(%rip), %xmm0             #
                                # LOE rbx r14 eax esi r12d r13d r15d xmm0 xmm2 xmm3 xmm4 xmm5
..B1.47:                        # Preds ..B1.47 ..B1.46
                                # Execution count [1.25e+01]
        incl      %esi                                          #80.72
        mulsd     %xmm0, %xmm3                                  #80.72
        cmpl      %eax, %esi                                    #80.72
        jb        ..B1.47       # Prob 82%                      #80.72
        jmp       ..B1.59       # Prob 100%                     #80.72
                                # LOE rbx r14 eax esi r12d r13d r15d xmm0 xmm2 xmm3 xmm4 xmm5
..B1.49:                        # Preds ..B1.40
                                # Execution count [2.25e+00]
        cltd                                                    #80.54
        xorl      %edx, %eax                                    #80.54
        movaps    %xmm5, %xmm3                                  #80.72
        subl      %edx, %eax                                    #80.54
        cmpl      $8, %eax                                      #80.72
        jl        ..B1.61       # Prob 10%                      #80.72
                                # LOE rbx r14 eax r12d r13d r15d xmm2 xmm3 xmm4 xmm5
..B1.50:                        # Preds ..B1.49
                                # Execution count [2.25e+00]
        movl      %eax, %esi                                    #80.72
        movl      %r13d, %ecx                                   #80.72
        movups    .L_2il0floatpacket.3(%rip), %xmm0             #80.72
        movaps    %xmm4, %xmm3                                  #80.72
        andl      $-8, %esi                                     #80.72
                                # LOE rbx r14 eax ecx esi r12d r13d r15d xmm0 xmm2 xmm3 xmm4 xmm5
..B1.51:                        # Preds ..B1.51 ..B1.50
                                # Execution count [1.25e+01]
        mulpd     %xmm0, %xmm3                                  #80.72
        mulpd     %xmm0, %xmm3                                  #80.72
        mulpd     %xmm0, %xmm3                                  #80.72
        addl      $8, %ecx                                      #80.72
        mulpd     %xmm0, %xmm3                                  #80.72
        cmpl      %esi, %ecx                                    #80.72
        jb        ..B1.51       # Prob 82%                      #80.72
                                # LOE rbx r14 eax ecx esi r12d r13d r15d xmm0 xmm2 xmm3 xmm4 xmm5
..B1.52:                        # Preds ..B1.51
                                # Execution count [2.25e+00]
        movaps    %xmm3, %xmm0                                  #80.72
        unpckhpd  %xmm3, %xmm0                                  #80.72
        mulsd     %xmm0, %xmm3                                  #80.72
                                # LOE rbx r14 eax esi r12d r13d r15d xmm2 xmm3 xmm4 xmm5
..B1.53:                        # Preds ..B1.52 ..B1.61
                                # Execution count [2.50e+00]
        cmpl      %eax, %esi                                    #80.72
        jae       ..B1.29       # Prob 10%                      #80.72
                                # LOE rbx r14 eax esi r12d r13d r15d xmm2 xmm3 xmm4 xmm5
..B1.54:                        # Preds ..B1.53
                                # Execution count [2.25e+00]
        movsd     .L_2il0floatpacket.1(%rip), %xmm0             #
                                # LOE rbx r14 eax esi r12d r13d r15d xmm0 xmm2 xmm3 xmm4 xmm5
..B1.55:                        # Preds ..B1.55 ..B1.54
                                # Execution count [1.25e+01]
        incl      %esi                                          #80.72
        mulsd     %xmm0, %xmm3                                  #80.72
        cmpl      %eax, %esi                                    #80.72
        jb        ..B1.55       # Prob 82%                      #80.72
        jmp       ..B1.29       # Prob 100%                     #80.72
                                # LOE rbx r14 eax esi r12d r13d r15d xmm0 xmm2 xmm3 xmm4 xmm5
..B1.57:                        # Preds ..B1.31
                                # Execution count [1.02e+00]
        movaps    %xmm5, %xmm3                                  #80.72
        testl     %r15d, %r15d                                  #80.54
        jns       ..B1.29       # Prob 50%                      #80.54
                                # LOE rbx r14 r12d r13d r15d xmm2 xmm3 xmm4 xmm5
..B1.58:                        # Preds ..B1.57
                                # Execution count [1.88e+00]
        movsd     .L_2il0floatpacket.4(%rip), %xmm2             #80.54
                                # LOE rbx r14 r12d r13d r15d xmm2 xmm3 xmm4 xmm5
..B1.59:                        # Preds ..B1.47 ..B1.45 ..B1.58
                                # Execution count [1.25e+00]
        movaps    %xmm3, %xmm0                                  #80.72
        movsd     .L_2il0floatpacket.4(%rip), %xmm3             #80.72
        divsd     %xmm0, %xmm3                                  #80.72
        jmp       ..B1.29       # Prob 100%                     #80.72
                                # LOE rbx r14 r12d r13d r15d xmm2 xmm3 xmm4 xmm5
..B1.60:                        # Preds ..B1.41
                                # Execution count [2.25e-01]: Infreq
        movl      %r13d, %esi                                   #80.72
        jmp       ..B1.45       # Prob 100%                     #80.72
                                # LOE rbx r14 eax esi r12d r13d r15d xmm2 xmm3 xmm4 xmm5
..B1.61:                        # Preds ..B1.49
                                # Execution count [2.25e-01]: Infreq
        movl      %r13d, %esi                                   #80.72
        jmp       ..B1.53       # Prob 100%                     #80.72
                                # LOE rbx r14 eax esi r12d r13d r15d xmm2 xmm3 xmm4 xmm5
..B1.62:                        # Preds ..B1.32
                                # Execution count [2.25e-01]: Infreq
        movl      %r13d, %esi                                   #80.54
        jmp       ..B1.36       # Prob 100%                     #80.54
                                # LOE rbx r14 eax esi r8d r12d r13d r15d xmm2 xmm4 xmm5
..B1.63:                        # Preds ..B1.30
                                # Execution count [4.50e-01]: Infreq
        movq      24(%rsp), %r15                                #[spill]
        movq      32(%rsp), %r12                                #[spill]
	.cfi_restore 12
        jmp       ..B1.15       # Prob 100%                     #
        .align    16,0x90
                                # LOE r12 r14 r15
	.cfi_endproc
# mark_end;
	.type	main,@function
	.size	main,.-main
	.data
	.align 4
	.align 4
var.1169.0.4:
	.long	2
	.section .rodata, "a"
	.align 16
	.align 16
hello.1169.0.0.4:
	.long	1819043176
	.word	111
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.section .rodata.str1.4, "aMS",@progbits,1
	.align 4
	.align 4
il0_peep_printf_format_0:
	.long	1635086661
	.word	108
	.data
# -- End  main
	.text
# -- Begin  ilog2
	.text
# mark_begin;
       .align    16,0x90
	.globl ilog2
# --- ilog2(uint64_t)
ilog2:
# parameter 1: %rdi
..B2.1:                         # Preds ..B2.0
                                # Execution count [1.00e+00]
	.cfi_startproc
..___tag_value_ilog2.49:
..L50:
                                                         #15.1
        pushq     %r15                                          #15.1
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
        subq      $16, %rsp                                     #15.1
	.cfi_def_cfa_offset 32
        movq      %rdi, %r15                                    #15.1
        movq      %r15, %rsi                                    #16.15
        lea       (%rsp), %rdi                                  #16.15
        call      __ktoq                                        #16.15
                                # LOE rbx rbp r12 r13 r14 r15
..B2.4:                         # Preds ..B2.1
                                # Execution count [1.00e+00]
        movq      8(%rsp), %rdx                                 #16.15
        movl      $16383, %eax                                  #18.20
        sarq      $48, %rdx                                     #18.15
        subq      %rax, %rdx                                    #18.20
        movq      $-1, %rax                                     #18.9
        testq     %r15, %r15                                    #18.9
        cmovne    %rdx, %rax                                    #18.9
        addq      $16, %rsp                                     #18.9
	.cfi_def_cfa_offset 16
	.cfi_restore 15
        popq      %r15                                          #18.9
	.cfi_def_cfa_offset 8
        ret                                                     #18.9
        .align    16,0x90
                                # LOE
	.cfi_endproc
# mark_end;
	.type	ilog2,@function
	.size	ilog2,.-ilog2
	.data
# -- End  ilog2
	.text
# -- Begin  expon
	.text
# mark_begin;
       .align    16,0x90
	.globl expon
# --- expon(double, double)
expon:
# parameter 1: %xmm0
# parameter 2: %xmm1
..B3.1:                         # Preds ..B3.0
                                # Execution count [1.00e+00]
	.cfi_startproc
..___tag_value_expon.58:
..L59:
                                                         #22.1
        movaps    %xmm1, %xmm3                                  #22.1
        cvttsd2si %xmm3, %eax                                   #24.31
        cltd                                                    #24.22
        xorl      %edx, %eax                                    #24.22
        movaps    %xmm0, %xmm2                                  #22.1
        subl      %edx, %eax                                    #24.22
        movsd     .L_2il0floatpacket.4(%rip), %xmm1             #23.11
        testl     %eax, %eax                                    #24.22
        jle       ..B3.10       # Prob 50%                      #24.22
                                # LOE rbx rbp r12 r13 r14 r15 eax xmm1 xmm2 xmm3
..B3.2:                         # Preds ..B3.1
                                # Execution count [9.00e-01]
        cmpl      $8, %eax                                      #24.22
        jl        ..B3.13       # Prob 10%                      #24.22
                                # LOE rbx rbp r12 r13 r14 r15 eax xmm1 xmm2 xmm3
..B3.3:                         # Preds ..B3.2
                                # Execution count [9.00e-01]
        movl      %eax, %edx                                    #24.22
        movaps    %xmm2, %xmm0                                  #21.8
        movups    .L_2il0floatpacket.2(%rip), %xmm1             #23.11
        andl      $-8, %edx                                     #24.22
        unpcklpd  %xmm0, %xmm0                                  #21.8
        xorl      %ecx, %ecx                                    #24.22
                                # LOE rbx rbp r12 r13 r14 r15 eax edx ecx xmm0 xmm1 xmm2 xmm3
..B3.4:                         # Preds ..B3.4 ..B3.3
                                # Execution count [5.00e+00]
        mulpd     %xmm0, %xmm1                                  #25.6
        mulpd     %xmm0, %xmm1                                  #25.6
        mulpd     %xmm0, %xmm1                                  #25.6
        addl      $8, %ecx                                      #24.22
        mulpd     %xmm0, %xmm1                                  #25.6
        cmpl      %edx, %ecx                                    #24.22
        jb        ..B3.4        # Prob 82%                      #24.22
                                # LOE rbx rbp r12 r13 r14 r15 eax edx ecx xmm0 xmm1 xmm2 xmm3
..B3.5:                         # Preds ..B3.4
                                # Execution count [9.00e-01]
        movaps    %xmm1, %xmm0                                  #23.11
        unpckhpd  %xmm1, %xmm0                                  #23.11
        mulsd     %xmm0, %xmm1                                  #23.11
                                # LOE rbx rbp r12 r13 r14 r15 eax edx xmm1 xmm2 xmm3
..B3.6:                         # Preds ..B3.5 ..B3.13
                                # Execution count [1.00e+00]
        cmpl      %eax, %edx                                    #24.22
        jae       ..B3.10       # Prob 9%                       #24.22
                                # LOE rbx rbp r12 r13 r14 r15 eax edx xmm1 xmm2 xmm3
..B3.8:                         # Preds ..B3.6 ..B3.8
                                # Execution count [5.00e+00]
        incl      %edx                                          #24.22
        mulsd     %xmm2, %xmm1                                  #25.6
        cmpl      %eax, %edx                                    #24.22
        jb        ..B3.8        # Prob 82%                      #24.22
                                # LOE rbx rbp r12 r13 r14 r15 eax edx xmm1 xmm2 xmm3
..B3.10:                        # Preds ..B3.8 ..B3.6 ..B3.1
                                # Execution count [1.00e+00]
        pxor      %xmm2, %xmm2                                  #26.2
        comisd    %xmm3, %xmm2                                  #26.11
        jbe       ..B3.12       # Prob 50%                      #26.11
                                # LOE rbx rbp r12 r13 r14 r15 xmm1
..B3.11:                        # Preds ..B3.10
                                # Execution count [5.00e-01]
        movaps    %xmm1, %xmm2                                  #26.18
        movsd     .L_2il0floatpacket.4(%rip), %xmm1             #26.18
        divsd     %xmm2, %xmm1                                  #26.18
                                # LOE rbx rbp r12 r13 r14 r15 xmm1
..B3.12:                        # Preds ..B3.11 ..B3.10
                                # Execution count [1.00e+00]
        movaps    %xmm1, %xmm0                                  #27.9
        ret                                                     #27.9
                                # LOE
..B3.13:                        # Preds ..B3.2
                                # Execution count [9.00e-02]: Infreq
        xorl      %edx, %edx                                    #24.22
        jmp       ..B3.6        # Prob 100%                     #24.22
        .align    16,0x90
                                # LOE rbx rbp r12 r13 r14 r15 eax edx xmm1 xmm2 xmm3
	.cfi_endproc
# mark_end;
	.type	expon,@function
	.size	expon,.-expon
	.data
# -- End  expon
	.section .rodata, "a"
	.space 12, 0x00 	# pad
	.align 16
.L_2il0floatpacket.0:
	.byte	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3e,0x40,0x00,0x00,0x00,0x00,0x00,0x00
	.type	.L_2il0floatpacket.0,@object
	.size	.L_2il0floatpacket.0,16
	.align 16
.L_2il0floatpacket.2:
	.long	0x00000000,0x3ff00000,0x00000000,0x3ff00000
	.type	.L_2il0floatpacket.2,@object
	.size	.L_2il0floatpacket.2,16
	.align 16
.L_2il0floatpacket.3:
	.long	0x38000000,0x3fd33333,0x38000000,0x3fd33333
	.type	.L_2il0floatpacket.3,@object
	.size	.L_2il0floatpacket.3,16
	.align 8
.L_2il0floatpacket.1:
	.long	0x38000000,0x3fd33333
	.type	.L_2il0floatpacket.1,@object
	.size	.L_2il0floatpacket.1,8
	.align 8
.L_2il0floatpacket.4:
	.long	0x00000000,0x3ff00000
	.type	.L_2il0floatpacket.4,@object
	.size	.L_2il0floatpacket.4,8
	.section .rodata.str1.4, "aMS",@progbits,1
	.space 2, 0x00 	# pad
	.align 4
.L_2__STRING.0:
	.long	7695397
	.type	.L_2__STRING.0,@object
	.size	.L_2__STRING.0,4
	.align 4
.L_2__STRING.1:
	.long	1970039845
	.long	622865696
	.long	175467628
	.long	1313819733
	.long	1095589703
	.long	540876888
	.long	175467557
	.byte	0
	.type	.L_2__STRING.1,@object
	.size	.L_2__STRING.1,29
	.space 3, 0x00 	# pad
	.align 4
.L_2__STRING.4:
	.long	1478850608
	.long	807415072
	.long	542647672
	.long	2016419885
	.long	168450085
	.byte	0
	.type	.L_2__STRING.4,@object
	.size	.L_2__STRING.4,21
	.space 3, 0x00 	# pad
	.align 4
.L_2__STRING.3:
	.long	6513249
	.type	.L_2__STRING.3,@object
	.size	.L_2__STRING.3,4
	.align 4
.L_2__STRING.5:
	.long	757101349
	.long	175318304
	.byte	0
	.type	.L_2__STRING.5,@object
	.size	.L_2__STRING.5,9
	.space 3, 0x00 	# pad
	.align 4
.L_2__STRING.8:
	.long	808594981
	.long	539828326
	.long	808594981
	.long	539828326
	.long	1715023397
	.long	622865696
	.long	174471470
	.byte	0
	.type	.L_2__STRING.8,@object
	.size	.L_2__STRING.8,29
	.space 3, 0x00 	# pad
	.align 4
.L_2__STRING.9:
	.long	622879781
	.long	1680154736
	.long	174335264
	.byte	0
	.type	.L_2__STRING.9,@object
	.size	.L_2__STRING.9,13
	.space 3, 0x00 	# pad
	.align 4
.L_2__STRING.10:
	.long	175467557
	.byte	0
	.type	.L_2__STRING.10,@object
	.size	.L_2__STRING.10,5
	.space 3, 0x00 	# pad
	.align 4
.L_2__STRING.12:
	.long	1819043144
	.long	1867980911
	.long	6581362
	.type	.L_2__STRING.12,@object
	.size	.L_2__STRING.12,12
	.align 4
.L_2__STRING.13:
	.long	537555749
	.long	684837
	.type	.L_2__STRING.13,@object
	.size	.L_2__STRING.13,8
	.align 4
.L_2__STRING.14:
	.word	29477
	.byte	0
	.type	.L_2__STRING.14,@object
	.size	.L_2__STRING.14,3
	.space 1, 0x00 	# pad
	.align 4
.L_2__STRING.15:
	.long	1819043144
	.long	1867980911
	.long	174353522
	.byte	0
	.type	.L_2__STRING.15,@object
	.size	.L_2__STRING.15,13
	.section .rodata.str1.32, "aMS",@progbits,1
	.align 32
	.align 32
.L_2__STRING.2:
	.long	1095254869
	.long	1095589714
	.long	540876888
	.long	1970039845
	.long	1428172064
	.long	1414678611
	.long	1480674655
	.long	622869792
	.long	544566380
	.long	1230315565
	.long	1298093134
	.long	1025529921
	.long	1819026720
	.long	539828341
	.long	1313819733
	.long	1095589703
	.long	540876888
	.long	1970039845
	.long	1814048032
	.long	1815242607
	.long	1280649256
	.long	1598508623
	.long	693649741
	.long	540876841
	.long	174476325
	.word	10
	.type	.L_2__STRING.2,@object
	.size	.L_2__STRING.2,102
	.data
	.section .note.GNU-stack, ""
// -- Begin DWARF2 SEGMENT .eh_frame
	.section .eh_frame,"a",@progbits
.eh_frame_seg:
	.align 8
# End
