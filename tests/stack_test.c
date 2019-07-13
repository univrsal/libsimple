#include <libsimple.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void stack_test(void)
{
	struct libs_stack *stack = NULL;
	/* Test default stack */
	stack = libs_stack();
	assert(stack != NULL);
	libs_stack_destroy(stack);

	/* Test preallocated stack */
	stack = libs_stack_create(5, sizeof(int));
	assert(stack != NULL);

	bool success = 1;
	for (int i = 0; i < 6; i++) {
		if (!libs_stack_push(stack, &i)) {
			printf("Push at %i failed\n", i);
			success = 0;
			break;
		}
	}
	assert(success);

	printf("Top: %i\n", *(int*) libs_stack_top(stack));
	libs_stack_destroy(stack);

	stack = libs_stack();
	for (int i = 0; i < 10; i++)
		libs_stack_push(stack, &i);
	int* copy = libs_stack_fetch(stack);
	printf("Copy: %i\n", *copy);
	libs_stack_destroy(stack);
	free(copy);
}
