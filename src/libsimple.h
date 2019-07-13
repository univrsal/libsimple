#ifndef LIBSIMPLE_H
#define LIBSIMPLE_H

#ifdef __cplusplus
extern "C" {
#endif

/* If you want libsimple to use typedefs
 * use #define LIB_SIMPLE_TYPEDEF 1
 */

/* These headers can also be included individually
 * if only a specific module is needed.
 * If this is done, make sure to surround the include
 * statement with 'extern "C"', if C++ is used.
 */
#include "stack.h"
#include "str.h"
#include "array.h"
#include "list.h"
#include "tree.h"

#ifdef __cplusplus
}
#endif

#endif /* Header guard */
