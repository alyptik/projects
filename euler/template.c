// template.c

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

//#include "template.h"

int main(int argc, char **argv) {
	printf("\nargc: \"%d\"\t", argc);
	for (int i = 0; i < argc; i++)
		printf("argv[%d]: \"%s\"\t", argc - 1, *(argv + argc - 1));
	printf("\nerrno: \"%d\"\n", errno);
	return 0;
}
