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

#ifndef LIB_SIMPLE_ARRAY_H
#define LIB_SIMPLE_ARRAY_H
#include "types.h"

struct libs_array;

#ifdef LIB_SIMPLE_TYPEDEF
typedef struct libs_array libs_array_t;
#endif

/* Create an array of provided size
 * returns the direct pointer to the array
 * memory is zeroed
 * @item_size	size of an individual item
 * @count	item count of array
 * @return 	direct pointer to array
 */
extern DECLSPEC void* LIBS_CALL
libs_array(size_t item_size, size_t count);

/* Deletes array */
extern DECLSPEC void LIBS_CALL
libs_array_destroy(void *array);

/* Gets the size of an array
 * only use the pointer returned
 * by libs_array()
 */
extern DECLSPEC size_t LIBS_CALL
libs_array_count(void *array);

/* Gets the size of an individual
 * item of the array. only use the
 * pointer returned by
 * libs_array()
 */
extern DECLSPEC size_t LIBS_CALL
libs_array_item_size(void *array);

/* Resizes the array to the provided
 * lenght.
 * If size was increased new memory
 * is zeroed
 */
extern DECLSPEC bool LIBS_CALL
libs_array_resize(void *array, size_t count);

#define libs_array_for(arr, index) for (index = 0; index < \
        libs_array_count(arr); ++index)
#define libs_array_foreach(arr, index, item) for (index = 0; index < \
        libs_array_count(arr) && ((item = arr[index]) || 1); ++index)

/* A pointer to a function wich returns
 * the difference in value between a and b:
 * return a - b
 * this is used when sorting an array
 */
typedef int (libs_array_compare_t)(const void *a, const void *b);

/* Sorts the provided array
 * with quicksort and a provided
 * comparsion method. This uses the stdlib implementation
 * of quicksort
 */
extern DECLSPEC void LIBS_CALL
libs_array_sort(void *array, libs_array_compare_t* comp);
#endif /* Header guard */
