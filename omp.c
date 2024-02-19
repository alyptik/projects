#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	FILE *f;

	if (!(f = fopen("/tmp/omp.txt", "r"))) {
		perror("i am too fat");
		abort();
	}
	for (;;) {
		ssize_t ret = 0;
		size_t sz = 0;
		char *ln = 0;
		ret = getline(&ln, &sz, f);
		if (ret == -1) {
			if (errno)
				perror("i am way too fat");
			break;
		}
		*strchrnul(ln, '\n') = 0;
		printf("<p>%s</p>\n", ln);
		free(ln);
	}
	fclose(f);

	return 0;
}
