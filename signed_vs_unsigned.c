#include <stdio.h>
#include <time.h>

int isprime_slow(int num) {
    if (num % 2 == 0)
        return num == 2;
    for (int i = 3; i < num; i += 2) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int unsigned_isprime_slow(unsigned int num) {
    if (num % 2 == 0)
        return num == 2;
    for (unsigned int i = 3; i < num; i += 2) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int isprime_fast(int num) {
    if (num % 2 == 0)
        return num == 2;
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int unsigned_isprime_fast(unsigned int num) {
    if (num % 2 == 0)
        return num == 2;
    for (unsigned int i = 3; i * i <= num; i += 2) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int div_fast(int num) {
    int i;
    for (i = 1; num / i; i++);
    return i;
}

int unsigned_div_fast(unsigned int num) {
    unsigned int i;
    for (i = 1; num / i; i++);
    return i;
}

int main(void) {
    int a[] = {
        294967291, 0, 294367293, 0, 294967293, 0, 294967241, 1, 294967251, 0,
        294965291, 0, 294966291, 0, 294963293, 0, 294927293, 1, 294961293, 0,
        294917293, 0, 294167293, 0, 294267293, 0, 294367293, 0, 294467293, 0,
    };
    struct testcase { int (*fun)(); const char *name; clock_t t; } test[] = {
        { isprime_slow, "isprime_slow", 0 },
        { unsigned_isprime_slow, "unsigned_isprime_slow", 0 },
        { isprime_fast, "isprime_fast", 0 },
        { unsigned_isprime_fast, "unsigned_isprime_fast", 0 },
        { div_fast, "div_fast", 0 },
        { unsigned_div_fast, "unsigned_div_fast", 0 },
    };

    for (int n = 0; n < 4; n++) {
        clock_t t = clock();
        for (int i = 0; i < 30; i += 2) {
            if (test[n].fun(a[i]) != a[i + 1]) {
                printf("%s(%d) != %d\n", test[n].name, a[i], a[i + 1]);
            }
        }
        test[n].t = clock() - t;
    }
    for (int n = 0; n < 4; n++) {
        printf("%21s: %4ld.%03ldms\n", test[n].name, test[n].t / 1000, test[n].t % 1000);
    }
    for (int n = 0; n < 2; n++) {
	printf("%21s: %ld.%03ldμs\n", test[n].name, test[n].t / 100, test[n].t % 100);
    }

    return 0;
}
