#include <stdio.h>

static unsigned inputs[2][2] = {0};

/*
 * when inlined it just crashes without the
 * second safe() call
 */
void broken(void) {
/* static inline void broken(void) { */
	for (int i = 0; i < 4; ++i) {
		printf("broken: %d\n", i);
		if (inputs[i][0])
			return;
	}
}

void safe(void) {
	for (int i = 0; i < 4; ++i) {
		if (inputs[i][0])
			return;
		printf("safe: %d\n", i);
	}
}

/*
 * calls safe -> broken -> safe (???) then crashes
 */
int main(void) {
	safe();
	broken();

	return 0;
}
