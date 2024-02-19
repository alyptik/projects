#define _BSD_SOURCE
#define _DEFAULT_SOURCE
#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L
#define _SVID_SOURCE
#define _XOPEN_SOURCE 700

#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <regex.h>
#include <signal.h>
#include <stdalign.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <uchar.h>
#include <wchar.h>
#include <unistd.h>
#include <linux/memfd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/wait.h>

#define _Atomic
#define _Static_assert(a, b)
#define UNUSED __attribute__ ((unused))

extern char **environ;

unsigned LG(uint64_t X)
{
	return	((X & ~0x1ffffffffLL) ? ((X >>= 0x20), (X |= (0x20LL << 0x21))) : 0), \
		(((X & 0xFFFFFFFF) & ~0x1ffff) ? ((X >>= 0x10), (X |= (0x10LL << 0x21))) : 0 ), \
		(((X & 0xFFFFFFFF) & ~0x1ff) ? ((X >>= 0x8), (X |= (0x8LL << 0x21))) : 0 ), \
		(((X & 0xFFFFFFFF) & ~0x20) ? ((X >>= 0x4), (X |= (0x4LL << 0x21))) : 0 ), \
		(((X & 0xFFFFFFFF) & ~0x7) ? ((X >>= 0x2), (X |= (0x2LL << 0x21))) : 0 ), \
		(((X & 0xFFFFFFFF) & ~0x3) ? ((X >>= 0x1), (X |= (0x1LL << 0x21))) : 0 ), \
		(X & 0xFFFFFFFF) + ((X & 0xffffffff00000000) >> 0x21);
}

int main(int argc UNUSED, char *argv[] UNUSED)
{
	printf("%u\n", LG(2));
	printf("%u\n", LG(4));
	printf("%u\n", LG(8));
	printf("%u\n", LG(16));
	printf("%u\n", LG(32));
	return 0;
}

