#include <libsimple.h>
#include <assert.h>

int main(void)
{
	struct libs_stack* stack = NULL;
	/* Test default stack */
	stack = libs_stack_create();
	assert(stack != NULL);
	libs_stack_destroy(stack);
	
	/* Test preallocated stack */
	stack = libs_stack_create(5, sizeof(int));
	assert(stack != NULL);

}
