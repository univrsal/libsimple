#include <libsimple.h>
#include <assert.h>

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

	for (int i = 0; i < 6; i++) {
		if (!libs_stack_push(stack, &i)) {
			printf("Push at %i failed\n", i);
			break;
		}
	}

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
