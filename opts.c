#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* getopts variables */
extern char *optarg;
extern int optind, opterr, optopt;

int main(int argc, char *argv[])
{
	int opt;
	char const *optstring = argv[1];

	/* print out cmdline original */
	printf("original = \"%s", argv[0]);
	for (size_t idx = 1; argv[idx]; idx++)
		printf(" %s", argv[idx]);
	puts("\"");
	/* remove the optstring (argv[1]) from arguments */
	for (size_t i = 1; i < (size_t)argc; i++)
		argv[i] = argv[i + 1];
	argc--;
	/* print out optstring */
	printf("optstring = \"%s\"\n", optstring);
	/* print out cmdline */
	printf("argc = \"%d\"\nargv = \"%s", argc, argv[0]);
	for (size_t idx = 1; argv[idx]; idx++)
		printf(" %s", argv[idx]);
	puts("\"");

	/* don't print an error if option not found */
	opterr = 0;
	/* reset option indices to reuse argv */
	optind = 1;

	/* parse options */
	while ((opt = getopt(argc, argv, optstring)) != -1) {
		switch (opt) {
		case '?':
			printf("option \"%c\" not implemented.\n", optopt);
			break;

		default: {
				/* index of the option */
				size_t this_optind = optind - 1;
				char optchar[2] = {0};
				optchar[0] = opt;
				/* handle weird cases like `-vvvvvvv` */
				if (argv[this_optind][0] != '-')
					break;
				/* check if actually an argument index */
				if (strpbrk(optstring, optchar)[1] == ':' && !strcmp(optarg, argv[optind - 1]))
					this_optind--;
				printf("argv[%zu] = \"%s\", this_optind = \"%zu\", optind = \"%d\", optarg = \"%s\"\n",
					this_optind, argv[this_optind], this_optind, optind, optarg);
				break;
			}
		}
	}

	return 0;
}
