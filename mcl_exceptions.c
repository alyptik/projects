#ifndef MCL_EXCEPTIONS_H
#define MCL_EXCEPTIONS_H

#if defined(__cplusplus) || !defined(__STDC__) || !__STDC_HOSTED__ || __STDC_VERSION__ < 199901L
    #error "MCL exception handling requires a hosted C99 (or newer) implementation."
#endif

#include <assert.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdlib.h>
#if __STDC_VERSION__ >= 201112L
    #include <stdnoreturn.h>
    #ifndef __STDC_NO_THREADS__
        #include <threads.h>
    #else
        #define thread_local
    #endif
#else
    #define noreturn
    #define thread_local
#endif

enum mcl_exceptionstate {
    MCL_TRY,
    MCL_CATCH,
    MCL_FINALLY
};

struct mcl_exceptionframe {
    struct mcl_exceptionframe *prev;
    jmp_buf context;
    enum mcl_exceptionstate state;
    int exception;
    bool mustcatch;
};

extern thread_local struct mcl_exceptionframe *mcl_exceptionstack;

static inline void mcl_pushexceptionframe(struct mcl_exceptionframe **const exceptionstack) {
    struct mcl_exceptionframe *topframe = malloc(sizeof *topframe);

    assert(topframe != NULL);
    topframe->prev = *exceptionstack;
    topframe->state = MCL_TRY;
    topframe->mustcatch = false;
    *exceptionstack = topframe;
}

static inline void mcl_popexceptionframe(struct mcl_exceptionframe **const exceptionstack) {
    struct mcl_exceptionframe *topframe = *exceptionstack;

    *exceptionstack = topframe->prev;
    free(topframe);
}

static inline noreturn void mcl_throw(struct mcl_exceptionframe **const exceptionstack, const int exception) {

    assert(*exceptionstack != NULL);
    (*exceptionstack)->exception = exception;
    (*exceptionstack)->mustcatch = true;

    switch ((*exceptionstack)->state) {
    case MCL_TRY:
        longjmp((*exceptionstack)->context, (*exceptionstack)->state = MCL_CATCH);
    case MCL_CATCH:
        longjmp((*exceptionstack)->context, (*exceptionstack)->state = MCL_FINALLY);
    case MCL_FINALLY:
        assert((*exceptionstack)->prev != NULL);
        (*exceptionstack)->prev->exception = (*exceptionstack)->exception;
        (*exceptionstack)->prev->mustcatch = (*exceptionstack)->mustcatch;
        mcl_popexceptionframe(exceptionstack);
        longjmp((*exceptionstack)->context, (*exceptionstack)->state = MCL_CATCH);
    }

    exit(EXIT_FAILURE);
}

#define try                                                                                                                                         \
    for (bool mcl_done = (mcl_pushexceptionframe(&mcl_exceptionstack), false); mcl_done != true;                                                    \
         mcl_exceptionstack->state != MCL_FINALLY ? longjmp(mcl_exceptionstack->context, mcl_exceptionstack->state = MCL_FINALLY)                   \
                                                  : mcl_exceptionstack->mustcatch ? mcl_throw(&mcl_exceptionstack, mcl_exceptionstack->exception)   \
                                                                                  : (mcl_done = true,                                               \
                                                                                     mcl_popexceptionframe(&mcl_exceptionstack)))                   \
        if (setjmp(mcl_exceptionstack->context) == MCL_TRY)

#define catch(e)                                                                                                                                    \
        else if (mcl_exceptionstack->state == MCL_CATCH && mcl_exceptionstack->exception == (e) && !(mcl_exceptionstack->mustcatch = false))

#define mcl_catchany                                                                                                                                \
        else if (mcl_exceptionstack->state == MCL_CATCH)

#define finally                                                                                                                                     \
        else if (mcl_exceptionstack->state == MCL_FINALLY)

#define throw(e)                                                                                                                                    \
    do                                                                                                                                              \
        mcl_throw(&mcl_exceptionstack, mcl_exceptionstack->exception = e);                                                                          \
    while (false)

#if __STDC_VERSION__ < 201112L
    #undef noreturn
    #undef thread_local
#elif defined(__STDC_NO_THREADS__)
    #undef thread_local
#endif

#endif