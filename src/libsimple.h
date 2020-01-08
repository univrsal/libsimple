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

#ifdef __cplusplus
}
#endif

#endif /* Header guard */
