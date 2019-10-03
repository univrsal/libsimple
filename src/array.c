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

#include "array.h"
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

static int array_offset = 0;

struct libs_array {
    size_t count;		/* Array item count	*/
    size_t item_size;	/* Size of single item	*/
    void *arr;			/* Pointer to array	*/
};

void *libs_array(size_t item_size, size_t count)
{
    struct libs_array *arr = malloc(sizeof(struct libs_array));
    arr->item_size = item_size;
    arr->count = count;
    arr->arr = calloc(count, item_size);

    if (array_offset == 0)
        array_offset = (int) &arr->arr - (int) arr;

    /* Intentionally return pointer to array
     * so that it can be directly utilized
     */
    return (void*) &arr->arr;
}

/* Internal only */
struct libs_array *array_get(void *arr)
{
    assert(array_offset > 0);
    assert(arr);
    arr -= array_offset;
    return (struct libs_array *) arr;
}

void libs_array_destroy(void *array)
{
    struct libs_array *a = array_get(array);
    if (a) {
        free(a->arr);
        free(a);
    }
}

size_t libs_array_count(void *array)
{
    struct libs_array *a = array_get(array);
    if (a)
        return a->count;
    return 0;
}

size_t libs_array_item_size(void *array)
{
    struct libs_array *a = array_get(array);
    if (a)
        return a->item_size;
    return 0;
}

bool libs_array_resize(void *array, size_t count)
{
    struct libs_array *a = array_get(array);
    if (a) {
        if (a->arr = realloc(a->arr, count * a->item_size)) {
            if (a->count < count) {
                /* Set new memory to zero */
                a->arr = memset(a->arr, 0, a->count * a->item_size);
            }

            a->count = count;
            return true;
        }
    }
    return false;
}

void libs_array_sort(void *array, libs_array_compare_t* comp)
{
    if (!array || !comp)
        return;
    struct libs_array *a = array_get(array);
    qsort(array, a->count, a->item_size, comp);
}
