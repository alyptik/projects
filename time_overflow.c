#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	struct tm *tm_ptr;
	char buf[128] = {0};
	time_t inc, t_tmp, t;

	t = LONG_MAX / 2;
	do {
		inc = t;
		t *= 2;
		tm_ptr = gmtime(&t);
	} while (tm_ptr);

	t = inc;
	inc = 1;
	do {
		inc += (t - inc) / 2;
		t -= inc;
		tm_ptr = gmtime(&t);
	} while (!tm_ptr);

	t_tmp = t;
	for (; (tm_ptr = gmtime(&t)); t_tmp = t, t += (inc >> 6));
	t = t_tmp;
	for (inc = 1; (tm_ptr = gmtime(&t)); t_tmp = t, t += (inc <<= 1));

	do {
		t = t_tmp;
		for (inc /= 2; (tm_ptr = gmtime(&t)); t_tmp = t, t += inc);
	} while (inc - 1 > 0);

	/* sanity checks */
	t = t_tmp + 1;
	tm_ptr = gmtime(&t);
	assert(!tm_ptr);
	t = t_tmp;
	tm_ptr = gmtime(&t);
	assert(tm_ptr);
	/* print out results */
	strftime(buf, sizeof buf, "%c", tm_ptr);
	printf("%ld -- %s\n", t, buf);

	return 0;
}
