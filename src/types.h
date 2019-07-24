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
#ifndef LIB_SIMPLE_TYPES_H
#define LIB_SIMPLE_TYPES_H

#include <stdint.h>
#include <stddef.h>

#ifndef bool
#define bool	uint8_t
#define false	0
#define true	1
#endif

#ifdef _WIN32
#define DECLSPEC __declspec(dllexport)
#define LIBS_CALL __cdecl
#define FORCE_INLINE __forceinline
#elif defined LINUX
#define DECLSPEC
#define LIBS_CALL
#define FORCE_INLINE __attribute((always_inline)) static __inline__
#endif

#endif /* Header guard */
