#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/syscall.h>
#include <signal.h>
#include <limits.h>
#include <math.h>
#include <crypt.h>
#include <stdlib.h>

int cmp (const void *a, const void *b)
{
	return isgreater(*(float *)a, *(float *)b) ? 1 : (isless(*(float *)a, *(float *)b) ? -1 : 0);
}

/* const char *c = "return isgreater(*(float *)a, *(float *)b) ? 1 : (isless(*(float *)a, *(float *)b) ? -1 : 0);"; */
/* char c[] = { 0x74, 0x75, 0x72, 0x6e, 0x20, 0x69, 0x73, 0x67, 0x72, 0x65, 0x61, 0x74, 0x65, 0x72, 0x28, 0x2a, 0x28, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x2a, 0x29, 0x61, 0x2c, 0x20, 0x2a, 0x28, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x2a, 0x29, 0x62, 0x29, 0x20, 0x3f, 0x20, 0x31, 0x20, 0x3a, 0x20, 0x28, 0x69, 0x73, 0x6c, 0x65, 0x73, 0x73, 0x28, 0x2a, 0x28, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x2a, 0x29, 0x61, 0x2c, 0x20, 0x2a, 0x28, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x2a, 0x29, 0x62, 0x29, 0x20, 0x3f, 0x20, 0x2d, 0x31, 0x20, 0x3a, 0x20, 0x30, 0x29, 0x3b, 0x00 }; */

int main(int argc, char **argv) {
	float a[] = { 1.1f, 1.4f, 1.2f, 1.0f, 0.5f, 3.2f, 0.1f };
	/* float j = 1.0f, k = 0.4f; */
	/* int (*b)(const void*, const void*) = (int (*)(const void*, const void*))c; */
	int (*b)(const void*, const void*) = &cmp;
	/* printf("%p\n", (((*(int (*)())&c[0])))); */
	qsort(a, sizeof a/sizeof a[0], sizeof a[0], b);
	for (unsigned i=0; i<(sizeof a)/(sizeof a[0]); i++)
		printf("%.1f\n", a[i]);
	return 0;
}
