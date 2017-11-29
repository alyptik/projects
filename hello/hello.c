#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>

/* link with -D_GNU_SOURCE */
#include <crypt.h>

uint64_t ilog2(uint64_t x)
{
	__float128 y=x;
	__int128_t i = *(__int128_t*)&y;
	return x?(i>>112)-16383:-1;
}

double expon(double n, double e)
{
	double c = 1;
	for (int k = 0; k < abs((int)e); k++)
	    c *= n;
	c = (e < 0) ? 1/c : c;
	return c;
}

//char *crypt(const char*, const char*);
//char *crypt_r(const char*, const char*, struct crypt_data);

int main(int argc, char **argv) {

	uint64_t d, ulm = ULONG_MAX;
	scanf("%lu", &d);
	printf("%llu - %llu\nULONG_MAX = %lu\n", (unsigned long long)d, (unsigned long long)ilog2(d), ulm);
	printf("UCHAR_MAX = %llu - USHRT_MAX = %llu - UINT_MAX = %llu - ULONG_MAX = %llu - log2l((ULONG_MAX)) = %Lf\n\n",
		(unsigned long long)UCHAR_MAX,
		(unsigned long long)USHRT_MAX,
		(unsigned long long)UINT_MAX,
		(unsigned long long)ULONG_MAX,
		(long double)(log2l((ULONG_MAX))));

	const char *key = "abc", *salt = "abc";
	char  *hash, *hash2;
	unsigned int fl1 = ~0, fl2 = ~(unsigned int)0, fl3 = -1;
	printf("0x%X - 0x%X - 0x%X\n\n", fl1, fl2, fl3);
	struct crypt_data data;
	/* struct crypt_data *data = malloc(sizeof *data); */
	data.initialized = -1;

	hash = crypt(key, salt);
	hash2 = crypt_r(key, salt, &data);
	printf("%s - %s\n", hash, hash2);

	char hello[20] = "hello";
	hello[5] = 'l';
	int (*foobar)(const char *, ...) = printf;
	int (*pf)(const char *, ...) = printf;
	int i, var = 2, *pvar, *pvar2 = &var, count;
	float f1 = 0.7f, f2 = 10.0f, f3;
	int i1, i2;

	f3 = f1 * f2;
	i1 = (int)f3;
	i2 = (int)(f1 * f2);
	if (i1 != i2)
		printf("Not equal\n");
	else
		printf("Equal\n");
	signed int j = -2;
	double a = 0.1f, b = 3.0f, c;
	c = a * b;
	if (argc < 2)
		count = 1;
	else
		count =	atoi(argv[1]);
	for (i = 0; i < count; i++)
	    pf("%.20f - %.20f - %.9f - %.9f\n", a * b , c, (expon(a * b, i)), expon(c,i));

	pvar = &var;
	printf ("%d %p %d %d\n", var, pvar, *pvar2, j);
	printf ("%lu\n",sizeof(char));

	pid_t pid1 = fork();

	foobar("%s\n", "Hello World");
	foobar("%s\n %s\n", hello, hello[6]);
	for (i = 0; i < argc; i++)
		foobar("%s\n", argv[i]);
	printf("%s","Hello World\n");
	return 0;
}

