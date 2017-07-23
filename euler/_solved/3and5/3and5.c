#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define C char
#define I int
#define F float
#define D double
/*
typedef char C
typedef int I
typedef float F
typedef double D
*/

/*
 * If we list all the natural numbers below 10 that are multiples of
 * 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
 * Find the sum of all the multiples of 3 or 5 below 1000.
 */

#define TGT 999

struct {
	I a, b;
} *num;
//} num[TGT * 2 + 1];

int main(int argc, char **argv) {
	num = malloc(sizeof(I) * TGT * 2);
	I *final = malloc(sizeof(I) * TGT * 2), index = 0, sum = 0, sum2 = 0;
	for (I i=0; i <= TGT; i++) {
		//num[i].b = i % 5;
		//printf("%d - %d\n", num[i].a, num[i].b);
		if ((i % 3) == 0) {
			*(final + index) = i;
			(num + index)->a = i;
			index += 1;
		} else if ((i % 5) == 0) {
			//final[index] = i;
			//num[index].b = i;
			*(final + index) = i;
			(num + index)->b = i;
			index += 1;
		}
	}
	for (int i=0; i < index; i++) {
		sum2 += ((num + i)->a + (num + i)->b);
		sum += *(final + i);
		printf("Index: %d\tCVal: %d\tsum: %d\tsum2: %d\n", index, *(final + i), sum, sum2);
	}
	printf("sum: %d\tsum2: %d\n", sum, sum2);
	printf("num: %d\tfinal: %d\n", sizeof(*num), sizeof(*final));
	free(num);
	free(final);
	return 0;
}

