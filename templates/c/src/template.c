/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2018 Joey Pabalinas <joeypabalinas@gmail.com>
 */

#undef _GNU_SOURCE
#define _GNU_SOURCE

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

extern char **environ;

int main(int argc, char **argv)
{
	(void)argc, (void)argv;
	printf("%s\n", "<template>");

	return 0;
}
