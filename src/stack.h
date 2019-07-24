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
#ifndef LIB_SIMPLE_STACK_H
#define LIB_SIMPLE_STACK_H
#include "types.h"

struct libs_stack;

#if LIB_SIMPLE_TYPEDEF
typedef struct libs_stack libs_stack_t;
#endif

/* Creates an empty stack,
 * with auto_resize enabled,
 * so the stack will allocate more
 * memory if push() is called and
 * the current array can not hold
 * the new item.
 */
extern DECLSPEC struct libs_stack* LIBS_CALL
libs_stack(void);

/* Creates a stack with preallocated memory
 * and auto_resize disabled, so push() will
 * fail if an item is pushed, but the stack is
 * full.
 *
 * @argument count		amount of items for stack
 * @argument item_size	size of a signle item
 */
extern DECLSPEC struct libs_stack *LIBS_CALL
libs_stack_create(size_t count, size_t item_size);

extern DECLSPEC void LIBS_CALL
libs_stack_set_auto_resize(struct libs_stack* stack, bool val);

extern DECLSPEC void LIBS_CALL
libs_stack_destroy(struct libs_stack* stack);

/* Push item to the top of the stack
 * if stack is full this will return
 * libs_false and the item will not
 * be added. Data added here will
 * be free()'d once pop() reaches
 * the item, or the stack is destroyed
 * or emptied. Use libs_stack_push_cpy
 * to make a copy of data.
 * @argument stack	the stack
 * @argument data	data to push
 * @return		false for failure,
 * 			true for success
 */
extern DECLSPEC bool LIBS_CALL
libs_stack_push(struct libs_stack* stack, void* data);

/* Removes the top item of the stack
 * and free()'s it
 * @return 	false for failure
 * 		true for success
 */
extern DECLSPEC bool LIBS_CALL
libs_stack_pop(struct libs_stack* stack);

/* Like pop, but returns
 * a pointer to the data taken from the top of the stack
 * This is a copy of the data and has to be free()'d
 */
extern DECLSPEC void* LIBS_CALL
libs_stack_fetch(struct libs_stack* stack);

/* Returns the current size of the stack */
extern DECLSPEC size_t LIBS_CALL
libs_stack_count(const struct libs_stack* stack);

/* Returns a pointer to the top item */
extern DECLSPEC void* LIBS_CALL
libs_stack_top(const struct libs_stack* stack);

/* Returns a pointer to the bottom item */
extern DECLSPEC void* LIBS_CALL
libs_stack_bottom(const struct libs_stack* stack);

/* Returns true if there's no space in the stack
 * Will always return false if auto_resize is enabled
 */
extern DECLSPEC bool LIBS_CALL
libs_stack_full(const struct libs_stack* stack);

/* Returns libs_true if the stack contains no items */
extern DECLSPEC bool LIBS_CALL
libs_stack_empty(const struct libs_stack* stack);

#endif /* Header guard */
