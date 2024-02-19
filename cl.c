#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tok(size_t *cnt, FILE * f, int last)
{
	int ret;
	if (!cnt || !f)
		return EOF;
	ret = getc(f);
	if (ret == '\n' || (ret == EOF && last != '\n'))
		++*cnt;
	return ret;
}

void walk(size_t *lines, FILE *f) {
	for (int last = 0, c = tok(lines, f, last); c != EOF; last = c, c = tok(lines, f, last));
}

int main(int argc, char **argv)
{
	char *name = "stdin";
	FILE *f = stdin;

	/* special case no arguments */
	if (argc < 2) {
		size_t lines = 0;
		/* walk the file */
		walk(&lines, f);
		printf("%zu %s\n", lines, name);
		/* exit early */
		return 0;
	}

	/* skip "-" */
	if (argv[1] && strcmp(argv[1], "-")) {
		f = fopen(argv[1], "r");
	}

	/* walk each file */
	for (int i = 1; i < argc && f; i++) {
		size_t lines = 0;

		name = argv[i] ? argv[i] : "stdin";

		/* handle "-" arguments */
		if (!argv[i] || !strcmp(name, "-")) {
			f = stdin;
			name = "stdin";
		/* else strip directory components */
		} else {
			name = strrchr(name, '/');
			name = name ?  name + 1 : argv[i];
			f = fopen(argv[i], "r");
		}

		/* calculate and print count */
		walk(&lines, f);
		printf("%zu %s\n", lines, name);

		/* cleanup */
		if (f != stdin)
			fclose(f);
	}

	return 0;
}
