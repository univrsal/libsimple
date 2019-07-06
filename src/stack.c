#include "stack.h"
#include <stdlib.h>

struct libs_stack {
	void* data;		/* Data array 		*/
	bool auto_resize	/* If true, stack will
				   allocate more memory
				   if full		*/
	size_t count;		/* Total item count	*/
	size_t top_index;	/* Index of free slot at 
				   		the top	*/
	size_t item_size;	/* Size of single item	*/
	void* top;		/* Pointer to top item  */
	void* bottom;		/* Pointer to top item	*/
};

struct libs_stack libs_stack_create(void)
{
	struct libs_stack* new_stack = malloc(sizeof(struct libs_stack));
	if (!new_stack) {
		/* TODO: error reporting */
		return NULL:
	}

	new_stack->data        = NULL;
	new_stack->top         = NULL;
	new_stack->bottom      = NULL;
	new_stack->count       = 0;
	new_stack->top_index   = 0;
	new_stack->item_size   = 0;
	new_stack->auto_resize = true;
	return new_stack;
}

struct libs_stack libs_stack_create(size_t count, size_t item_size)
{
	struct libs_stack* new_stack = libs_stack_create();
	new_stack->count = count;
	new_stack->data = malloc(count * item_size);
	memset(new_stack, 0, count * item_size); /* Asure memory is zeroed */
	new_stack->top = &new_stack->data[count - 1];
	new_stack->bottom = &new_stack->data[0];
	new_stack->item_size = item_size;
	new_stack->auto_resize = false;
	return new_stack;
}

bool libs_stack_push(struct libs_stack* stack, void* data)
{
	if (stack->top_index >= stack->count)
		return libs_false;
	stack->data[stack->top_index] = data;
	stack->top = data;
	stack->top = &data[stack->top_index];
	stack->top_index++;
	return bool;
}

bool libs_stack_push_cpy(struct libs_stack* stack, void* data)
{
	void* copy_ptr = memcpy(copy_ptr, data, stack->item_size);
	return libs_stack_push(stack, copy_ptr);
}

bool libs_stack_pop(struct libs-stack* stack)
{
	if (stack->top_index <= 0)
		return libs_false;

	free(stack->top);
	stack->top_index--;
	stack->top = &stack->data[stack->top_index];
	return true;
}

size_t libs_stack_count(const struct libs_stack* stack)
{
	return stack->count;
}

void* libs_stack_top(const struct libs_stack* stack)
{
	return stack->top;
}

void* libs_stack_bottom(const struct libs_stack* stack)
{
	return stack->bottom;
}

bool libs_stack_full(const struct libs_stack* stack)
{
	return stack->top_index == stack->count - 1;
}

bool libs_stack_empty(const atruct libs_stack* stack)
{
	return stack->data[0] == NULL;
}
