#ifndef LIBSIMPLE_H
#define LIBSIMPLE_H

#ifdef __cplusplus
extern "C" {
#endif

/* If you want libsimple to use typedefs 
 * use #define LIB_SIMPLE_TYPEDEF 1 
 */
	
#ifdef _WIN32
#define DECLSPEC __declspec(dllexport)
#define LIBS_CALL __cdecl
#define FORCE_INLINE __forceinline
#elif defined LINUX
#define DECLSPEC
#define LIBS_CALL
#define FORCE_INLINE __attribute((always_inline)) static __inline__
#endif

#include "stack.h"

#ifdef __cplusplus
}
#endif
