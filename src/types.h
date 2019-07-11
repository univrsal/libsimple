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
