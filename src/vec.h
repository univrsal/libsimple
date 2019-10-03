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

/* Unified vector data structure
 * For faster specific implementations
 * use vec2.h vec3.h and vec4.h
 */
#ifndef LIB_SIMPLE_VEC_H
#define LIB_SIMPLE_VEC_H

#include "types.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

#include <memory.h>
#include <malloc.h>
#include <stdarg.h>

#define LIBS_VEC_FLAG_2D	0b001000
#define LIBS_VEC_FLAG_3D	0b010000
#define LIBS_VEC_FLAG_4D	0b100000

/* BIT	Usage
 * 1-3	Type id
 * 4	Is 2D
 * 5	Is 3D
 * 6 	Is 4D
 */
enum libs_vec_type {
        libs_vec_2f = 0b001000,
        libs_vec_2i = 0b001001,
        libs_vec_3f = 0b010010,
        libs_vec_3i = 0b010011,
        libs_vec_4f = 0b100100,
        libs_vec_4i = 0b100101
};

struct libs_vec4f {
        union {
                struct { float x, y, z, w; };
                float p[4];
        };
};

struct libs_vec4i {
        union {
                struct { int x, y, z, w; };
                int p[4];
        };
};

struct libs_vec {
    void* ptr;
    enum libs_vec_type t;
};

#ifdef LIB_SIMPLE_TYPEDEF
typedef struct libs_vec libs_vec_t;
typedef enum libs_vec_type libs_vec_type_t;
#endif

extern DECLSPEC struct libs_vec *LIBS_CALL
libs_vector(enum libs_vec_type t, ...);

static inline DECLSPEC void LIBS_CALL libs_vector_free(struct libs_vec *v)
{
    free(v->ptr);
    free(v);
}

static inline size_t libs_vec_size(struct libs_vec *v)
{
    switch(v->t) {
    case libs_vec_2f:
        return sizeof(struct libs_vec2f);
    case libs_vec_2i:
        return sizeof(struct libs_vec2i);
    case libs_vec_3f:
        return sizeof(struct libs_vec3f);
    case libs_vec_3i:
        return sizeof(struct libs_vec3i);
    case libs_vec_4f:
        return sizeof(struct libs_vec4f);
    case libs_vec_4i:
        return sizeof(struct libs_vec4i);
    }
}

static inline void libs_vec_zero(struct libs_vec *v)
{
        memset(v->ptr, 0, libs_vec_size(v));
}

static inline bool libs_vec_dim_equal(const struct libs_vec *v1,
                                       const struct libs_vec *v2)
{
        bool result = false;
        if (v1->t & LIBS_VEC_FLAG_2D && v2->t & LIBS_VEC_FLAG_2D)
                result = true;
        else if (v1->t & LIBS_VEC_FLAG_3D && v2->t & LIBS_VEC_FLAG_3D)
                result = true;
        else if (v1->t & LIBS_VEC_FLAG_4D && v2->t & LIBS_VEC_FLAG_4D)
                result = true;
        return result;
}

static inline bool libs_vec_type_equal(const struct libs_vec *v1,
                                       const struct libs_vec *v2)
{
    return v1->t == v2->t;
}

extern DECLSPEC void LIBS_CALL libs_vec_set(struct libs_vec *v, ...);

extern DECLSPEC void LIBS_CALL libs_vec_add(struct libs_vec *dst, const struct libs_vec *v1,
                                const struct libs_vec *v2);

extern DECLSPEC void LIBS_CALL libs_vec_sub(struct libs_vec *dst, const struct libs_vec *v1,
                                const struct libs_vec *v2);

extern DECLSPEC void LIBS_CALL libs_vec_mul(struct libs_vec *dst, const struct libs_vec *v1,
                                const struct libs_vec *v2);

extern DECLSPEC void LIBS_CALL libs_vec_div(struct libs_vec *dst, const struct libs_vec *v1,
                                const struct libs_vec *v2);

#endif /* Header guard */
