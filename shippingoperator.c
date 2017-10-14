#include <stdio.h>

int main(void)
{
	int i = 100;
	// while i slides down to 0
	while ( i -- \
		    //\
		   //  \
	     _____//____\
	     \__________/
		       \
			> 0 ) {
		printf("test ");
	}

	return 0;
}
