/* Copyright (c) 2019 github.com/univrsal <universailp@web.de>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */
#include "stack.h"
#include <stdlib.h>
#include <memory.h>

struct libs_stack {
	void *data;		/* Data array 		*/
	bool auto_resize;	/* If true, stack
				   will allocate more
				   memory if full       */
	size_t count;		/* Total item count	*/
	size_t item_size;	/* Size of single item	*/
	size_t top_index;	/* Index of free
				   slot at the top	*/
	void *top;		/* Pointer to top item  */
	void *bottom;		/* Pointer to top item	*/
};

void *stack_at(const struct libs_stack *stack, size_t index)
{
	return (void*) (stack->data) + index * stack->item_size;
}

struct libs_stack *libs_stack(void)
{
	struct libs_stack *new_stack = malloc(sizeof(struct libs_stack));
	if (!new_stack) {
		/* TODO: error reporting */
		return NULL;
	}

	new_stack->data        = NULL;
	new_stack->top         = NULL;
	new_stack->bottom      = NULL;
	new_stack->count       = 0;
	new_stack->top_index   = 0;
	new_stack->auto_resize = true;
	return new_stack;
}

struct libs_stack *libs_stack_create(size_t count, size_t item_size)
{
	struct libs_stack* new_stack = libs_stack();
	new_stack->count = count;
	new_stack->data = malloc(count * item_size);
	new_stack->item_size = item_size;
	new_stack->top_index = 0;
	memset(new_stack->data, 0, count * item_size);
	new_stack->top = stack_at(new_stack, new_stack->top_index);
	new_stack->bottom = stack_at(new_stack, 0);
	new_stack->auto_resize = false;
	return new_stack;
}

void libs_stack_destroy(struct libs_stack *stack)
{
	if (!stack)
		return;
	free(stack->data);
	free(stack);
}

bool libs_stack_push(struct libs_stack *stack, void *data)
{
	if (stack->top_index >= stack->count) {
		if (stack->auto_resize) {
			size_t new_size = (++stack->count) * stack->item_size;
			stack->data = realloc(stack->data, new_size);
		} else {
			return false;
		}
	}

	stack->top = stack_at(stack, stack->top_index);
	memcpy(stack->top, data, stack->item_size);
	stack->top = data;
	stack->top_index++;
	return true;
}

void* libs_stack_fetch(struct libs_stack *stack)
{
	void* copy = malloc(stack->item_size);
	copy = memcpy(copy, stack->top, stack->item_size);
	return copy;
}

bool libs_stack_pop(struct libs_stack *stack)
{
    if (stack->top_index <= 0)
        return false;

    stack->top_index--;
    stack->top = stack_at(stack, stack->top_index);
    return true;
}

size_t libs_stack_count(const struct libs_stack *stack)
{
    return stack->count;
}

void *libs_stack_top(const struct libs_stack *stack)
{
    return stack->top;
}

void *libs_stack_bottom(const struct libs_stack *stack)
{
    return stack->bottom;
}

bool libs_stack_full(const struct libs_stack *stack)
{
    return stack->top_index == stack->count - 1;
}

bool libs_stack_empty(const struct libs_stack *stack)
{
    return stack->top_index == 0;
}
