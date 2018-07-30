#include <dlfcn.h>
/*
 * Defines LIBM_SO (which will be a
 * string such as "libm.so.6")
 */
#include <gnu/lib-names.h>
#include <stdio.h>
#include <stdlib.h>

typedef double (*dfun)(double);

int main(void)
{
	dfun cosine;
	char *error;
	void *handle = dlopen(LIBM_SO, RTLD_LAZY);

	if (!handle) {
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	/* Clear any existing error */
	dlerror();

	/*
	 * According to the ISO C standard, casting between function
	 * pointers and 'void *', as done above, produces undefined results.
	 * POSIX.1-2003 and POSIX.1-2008 accepted this state of affairs and
	 * proposed the following workaround:
	 *
	 * This (clumsy) cast conforms with the ISO C standard and will
	 * avoid any compiler warnings.
	 *
	 * The 2013 Technical Corrigendum to POSIX.1-2008 (a.k.a.
	 * POSIX.1-2013) improved matters by requiring that conforming
	 * implementations support casting 'void *' to a function pointer.
	 * Nevertheless, some compilers (e.g., gcc with the '-pedantic'
	 * option) may complain about the cast used in this program.
	 */
	*(void **)&cosine = dlsym(handle, "cos");
	error = dlerror();
	if (error != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(1);
	}
	printf("%f\n", cosine(2.0));
	dlclose(handle);

	return 0;
}
