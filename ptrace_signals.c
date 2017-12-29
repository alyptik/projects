#include <signal.h>
#include <stdio.h>
#include <sys/mman.h>

void function(void)
{
	printf("Copy protected: ok\n");
}

void handler(int signo)
{
	extern char smc;
	smc++;
}

#define TF 0x100

int main(int argc, char **argv)
{
	void (*fnp)(void);

	signal(SIGTRAP, handler);
	mprotect((void *)(0xfffff000 & (unsigned long)main), 4096, PROT_READ | PROT_WRITE);
	__asm__ volatile("pushfl; orl %0,(%%esp); popfl"::"i"(TF):"memory");
	__asm__ volatile("pushfl; andl %0,(%%esp); popfl"::"i"(~TF):"memory");
	__asm__ volatile("\nsmc:\n\t.byte 0xb7\n\t.long function":"=d"(fnp));
	/* __asm__ volatile("\nsmc:\n\t.long function":"=d"(fnp)); */
	fnp();
	return 1;
}
