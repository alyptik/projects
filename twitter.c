#ifndef _BSD_SOURCE
#  define _BSD_SOURCE
#endif
#ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
#endif
#ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#endif
#ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
#endif
#ifndef _SVID_SOURCE
#  define _SVID_SOURCE
#endif
#ifndef _XOPEN_SOURCE
#  define _XOPEN_SOURCE 700
#endif

#ifdef __INTEL_COMPILER
#  define _Float128 float_t
#else
#  include <complex.h>
#endif

#include <assert.h>
#include <ctype.h>
#include <error.h>
#include <errno.h>
#include <float.h>
#include <fcntl.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <pthread.h>
#include <regex.h>
#include <setjmp.h>
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
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <time.h>
#include <uchar.h>
#include <wchar.h>
#include <wctype.h>
#include <unistd.h>

extern char **environ;

#line 1

int main(int argc, char **argv)
{
	(void)argc, (void)argv;


	/*
	 * char enc[] = "-Atvt hrqgse, Cnikg", dec[sizeof enc] = "-Your friend, Alice";
	 * int key[sizeof enc - 1] = {0};
	 * for (size_t i = 0, j = 0; i < sizeof enc; i++, j++) {
	 *         if (!isalpha(enc[i])) {
	 *                 j--;
	 *         } else {
	 *                 printf("%d ", enc[i] - dec[i]);
	 *                 key[j] = enc[i] - dec[i];
	 *         }
	 * }
	 */

	/*
	 * {
	 *         char enc[] = "-Atvt hrqgse, Cnikg", dec[sizeof enc] = "-Your friend, Alice";
	 *         int key[sizeof enc - 1] = {0};
	 *         for (size_t i = 0, j = 0; i < sizeof enc; i++, j++) {
	 *                 if (!isalpha(enc[i])) {
	 *                         j--;
	 *                 } else {
	 *                         printf("%d ", enc[i] - dec[i]);
	 *                         key[j] = enc[i] - dec[i];
	 *                 }
	 *         }
	 *         puts("");
	 * }
	 */

	/*
	 * for (size_t i = 0, j = 0; i < sizeof enc; i++, j++) {
	 *         if (j > sizeof k / sizeof *k - 1)
	 *                 j = 0;
	 *
	 *         if (!isalpha(enc[i])) {
	 *                 printf("%c", enc[i]);
	 *                 j--;
	 *                 flag = true;
	 *                 continue;
	 *         }
	 *
	 *         int idx = j;
	 *         char lim[] = {'a', 'z'}, inc;
	 *
	 *         if (flag)
	 *                 idx = !idx ? idx : idx - 1;
	 *         if (isupper(enc[i]))
	 *                 lim[0] -= 0x20, lim[1] -= 0x20;
	 *         if (enc[i] + k[idx] > lim[1])
	 *                 inc = enc[i] + k[idx] - lim[1] - 1;
	 *         else
	 *                 inc = k[idx];
	 *
	 *         printf("%c", (enc[i] + k[idx] > lim[1]) ? (lim[0] + inc) : (enc[i] + inc));
	 *         flag = false;
	 * }
	 */

	char encrypted_message[] = "Otjfvknou kskgnl, K mbxg iurtsvcnb ksgq hoz atv. "
		"Vje xcxtyqrl vt ujg smewfv vrmcxvtg rwqr ju vhm ytsf "
		"elwepuqyez. -Atvt hrqgse, Cnikg";
	/* char encrypted_message[] = "Bjj rwkcs dwpyp fwz"; */

    	int key[] = {8, 2, 5, 1 ,2, 2, 0};
	size_t idx = 0, len = sizeof key / sizeof *key;
	char *decrypted_message = malloc(strlen(encrypted_message) + 1);
	decrypted_message[strlen(encrypted_message)] = 0;

	for (size_t i = 0; i < strlen(encrypted_message) + 1; i++, idx++) {
		char dec, cur, bounds[] = {'a', 'z'};

		if (idx > len - 1)
			idx = 0;

		if (!isalpha(encrypted_message[i])) {
			idx--;
			decrypted_message[i] = encrypted_message[i];
			continue;
		}

		if (isupper(encrypted_message[i]))
			bounds[0] -= 0x20, bounds[1] -= 0x20;
		if (encrypted_message[i] - key[idx] < bounds[0])
			dec = bounds[0] - (encrypted_message[i] - key[idx]) - 1;
		else
			dec = key[idx];
		if (encrypted_message[i] - key[idx] < bounds[0])
			cur = bounds[1] - dec;
		else
			cur = encrypted_message[i] - dec;
		decrypted_message[i] = cur;
	}

	puts(decrypted_message);
	return 0;
}
