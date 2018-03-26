#include <stdio.h>
#include <stddef.h>

int combinations(char *v, char *v_, size_t n, char *s, size_t c, int (*f)(char *, void *), void *o)
{
	size_t i;

	if (n == 0) {
	return f(v_, o);
	}
	for (i = 0; i < c; i++) {
	int r;
	*v = s[i];
	if ((r = combinations(v + 1, v_, n - 1, s, c, f, o)))
	    return r;
	}

	return 0;
}

int p(char *s, void *o)
{
	(void)o;
	puts(s);
	return 0;
}

int main(void)
{
	char v[4];
	combinations(v, v, 3, "ABC", 3, p, 0);
	return 0;
}
