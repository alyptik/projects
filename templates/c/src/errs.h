/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2018 Joey Pabalinas <joeypabalinas@gmail.com>
 */

#if !defined(ERRS_H)
#define ERRS_H

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* warning macros */
# define warn(fmt, args...) \
	do { \
		fprintf(stderr, "`%s`: [%s:%u] " fmt "\n", strerror(errno), __FILE__, __LINE__, ## args); \
	} while (0)
# define warnx(fmt, args... ) \
	do { \
		fprintf(stderr, "[%s:%u] " fmt "\n", __FILE__, __LINE__, ## args); \
	} while (0)
/* error macros */
# define err(fmt, args...) \
	do { \
		fprintf(stderr, "`%s`: [%s:%u] " fmt "\n", strerror(errno), __FILE__, __LINE__, ## args); \
		exit(1); \
	} while (0)
# define errx(fmt, args...) \
	do { \
		fprintf(stderr, "[%s:%u] " fmt "\n", __FILE__, __LINE__, ## args); \
		exit(1); \
	} while (0)

#endif /* !defined(ERRS_H) */
