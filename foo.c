#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void foo0(void){puts("0");}
void foo1(void){puts("1");}
void foo2(void){puts("2");}
void foo3(void){puts("3");}
void foo4(void){puts("4");}
void foo5(void){puts("5");}
void foo6(void){puts("6");}

#define CONCAT(a,b) a##b
#define FOO(i) &CONCAT(foo, i),

void (*foos[])(void) = {
	&foo0,
	#include "magic.h"
};

int main(void){
	srand(time(NULL));
	int i = rand()%8;
	foos[i]();
}