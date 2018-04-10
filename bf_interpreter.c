#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdnoreturn.h>

typedef uint64_t Cell;


typedef struct _llist {
	size_t n;
	struct _llist *next;
} list;

typedef struct {
	Cell *tape;
	size_t tapesize;
	size_t ptr;
	list *stack;
} bf_state;


#define error(...) _error(__FILE__, __LINE__, __VA_ARGS__)
noreturn void _error(const char *file, int line, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "ERROR %s:%d: ", file, line);
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	abort();
}

void *alloc(size_t size) {
	void *ret = calloc(1, size);
	if (!ret) {
		error("Error allocating.");
	}
	return ret;
}

#define INIT_TAPESIZE 512

bf_state init_state(void) {
	bf_state ret = {.tape = alloc(INIT_TAPESIZE * sizeof(Cell)), .tapesize = INIT_TAPESIZE, .ptr = 0, .stack = NULL};
	return ret;
}

bool valid_bf(const char *bf) {
	size_t nesting = 0;
	while (*bf) {
		if (*bf == '[') {
			nesting++;
		} else if (*bf == ']') {
			if (nesting == 0) {
				return false;
			}
			nesting--;
		}
		bf++;
	}
	if (nesting) {
		return false;
	}

	return true;
}


void interpret(const char *bf, bf_state *state) {
	char c;
	size_t i;
	for (i = 0; (c = bf[i]); i++) {
		switch (c) {
			case '>':
				if (++state->ptr > state->tapesize-1) {
					// "realloc" except it zeroes everything else
					bf_state oldstate = *state;
					state->tape = alloc(sizeof(Cell) * (state->tapesize *= 2));
					memcpy(state->tape, oldstate.tape, sizeof(Cell) * oldstate.tapesize);
					free(oldstate.tape);
				}
				break;
			case '<':
				// wrapping smenatics
				if ((state->ptr--) == 0) {
					state->ptr = state->tapesize-1;
				}
				break;
			case '+':
				state->tape[state->ptr]++;
				break;
			case '-':
				state->tape[state->ptr]--;
				break;
			case '.':
				putchar(state->tape[state->ptr]);
				break;
			case ',':
				state->tape[state->ptr] = getchar();
				break;
			case '[':
				{
					// seek to the matching ']'
					if (!state->tape[state->ptr]) {
						size_t nesting = 1;

						while (bf[i++] && nesting) {
							switch (bf[i]) {
								case '[':
									nesting++; break;
								case ']':
									nesting--; break;
							}
						}
						// got to the end of the code but didn't get to a final closing ]
						if (nesting) {
							error("INTERNAL ERROR!  Mismatched loop (this should never be called");
						} else {
							// oh, look how convenient!  We're just at the closing ] now.
							break;
						}
					}



					// push the current code index onto the stack
					list *old = state->stack;
					state->stack = alloc(sizeof(list));
					state->stack->n = i;
					state->stack->next = old;
				}
				break;
			case ']':
				if (!state->stack) {
					error("INTERNAL ERROR!  Mismatched loop (this should never be called");
				}
				if (state->tape[state->ptr]) {
					i = state->stack->n;
				} else {
					// pop off the top stack value, we're done with that loop
					list *old = state->stack->next;
					free(state->stack);
					state->stack = old;
				}
				break;
		}
	}
}

int main(int argc, char **argv) {
	if (argc == 1) {
		error("Required brainfuck code as command-line argument.");
	}
	if (!valid_bf(argv[1])) {
		error("You have invalid brainfuck (and how??  It's pretty fucking hard to get invalid brainfuck)");
	}


	bf_state state = init_state();
	interpret(argv[1], &state);
	free(state.tape);

	return 0;
}
