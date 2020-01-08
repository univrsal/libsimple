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
#include "test.h"
#include <libsimple.h>

void stack_test(void)
{
    BEGIN_TEST("Stack");
    struct libs_stack *stack = NULL;
    /* Test default stack */
    stack = libs_stack();
    assert(stack != NULL);
    libs_stack_destroy(stack);

    /* Test preallocated stack */
    stack = libs_stack_create(5, sizeof(int));
    assert(stack != NULL);

    bool fail_index = 1;
    for (int i = 0; i < 6; i++) {
        if (!libs_stack_push(stack, &i)) {
            printf("Push at %i failed\n", i);
            fail_index = i;
            break;
        }
    }
    assert(fail_index == 5);

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
