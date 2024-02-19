#include <stdio.h>

/*
 * when const it doesn't crash
 */
static unsigned inputs[10][2][1] = {0};
/* static const unsigned inputs[10][2][1] = {0}; */

/*
 * it falls through to a second safe()
 * call and overflows the stack.
 */
static inline void broken(void) {
/* void broken(void) { */
	for (int i = 0; i < 2; ++i) {
		printf("broken: %d\n", i);
		if (inputs[0][0][i])
			return;
	}
}

static inline void safe (void) {
/* void safe(void) { */
	for (int i = 0; i < 2; ++i) {
		if (inputs[0][0][i])
			return;
		printf("safe: %d\n", i);
	}
}

/*
 * gcc -O2 UB overealous optimizations
 *
 * "wtf where did ret go???"
 */
int main(void) {
	safe();
	broken();

	return 0;
}
