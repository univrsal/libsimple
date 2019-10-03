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
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int compare_int(const void *a, const void *b)
{
    int ia = *(int*)a;
    int ib = *(int*)b;
    return ia - ib;
}

void array_test(void)
{
    BEGIN_TEST("Array");
    int *arr = libs_array(sizeof(int), 10);
    assert(arr);
    assert(libs_array_count(arr) == 10);
    assert(libs_array_item_size(arr) == sizeof(int));

    size_t i;
    int val;
    libs_array_for(arr, i) {
        arr[i] = i;
    }

    libs_array_foreach(arr, i, val) {
        assert(val == i);
    }

    /* Reverse order for sorting test */
    libs_array_for(arr, i) {
        arr[i] = 9 - i;
        printf("arr[%i]: %i\n", i, 9 - i);
    }
    libs_array_sort(arr, &compare_int);
    printf("====== Sort result\n");

    /* Check if order was restored */
    libs_array_foreach(arr, i, val) {
        assert(val == i);
        printf("arr[%i]: %i\n", i, val);
    }

    //libs_array_destroy(arr);
}
