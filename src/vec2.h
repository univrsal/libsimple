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
#ifndef LIB_SIMPLE_VEC2
#define LIB_SIMPLE_VEC2
#include <math.h>
#include "types.h"

struct libs_vec2f {
        union {
                struct { float x, y; };
                float p[2];
        };
};

struct libs_vec2i {
        union {
                struct { int x, y; };
                int p[2];
        };
};

#if LIB_SIMPLE_TYPEDEF
typedef struct libs_vec2f libs_vec2f_t;
typedef struct libs_vec2i libs_vec2i_t;
#endif

static inline void libs_vec2f_zero(struct libs_vec2f *v)
{
        v->x = 0.f;
        v->y = 0.f;
}

static inline void libs_vec2i_zero(struct libs_vec2i *v)
{
       v->x = 0;
       v->y = 0;
}

static inline void libs_vec2f_set(struct libs_vec2f *v, float x, float y)
{
        v->x = x;
        v->y = y;
}

static inline void libs_vec2i_set(struct libs_vec2f *v, int x, int y)
{
        v->x = x;
        v->y = y;
}

static inline void libs_vec2f_add(struct libs_vec2f *dst,
                                  const struct libs_vec2f *v1,
                                  const struct libs_vec2f *v2)
{
        dst->x = v1->x + v2->x;
        dst->y = v1->y + v2->y;
}

static inline void libs_vec2i_add(struct libs_vec2i *dst,
                                  const struct libs_vec2i *v1,
                                  const struct libs_vec2i *v2)
{
        dst->x = v1->x + v2->x;
        dst->y = v1->y + v2->y;
}

static inline void libs_vec2f_sub(struct libs_vec2f *dst,
                                  const struct libs_vec2f *v1,
                                  const struct libs_vec2f *v2)
{
        dst->x = v1->x - v2->x;
        dst->y = v1->y - v2->y;
}

static inline void libs_vec2i_sub(struct libs_vec2i *dst,
                                  const struct libs_vec2i *v1,
                                  const struct libs_vec2i *v2)
{
        dst->x = v1->x - v2->x;
        dst->y = v1->y - v2->y;
}

static inline void libs_vec2f_mul(struct libs_vec2f *dst,
                                  const struct libs_vec2f *v1,
                                  const struct libs_vec2f *v2)
{
        dst->x = v1->x * v2->x;
        dst->y = v1->y * v2->y;
}

static inline void libs_vec2i_mul(struct libs_vec2i *dst,
                                  const struct libs_vec2i *v1,
                                  const struct libs_vec2i *v2)
{
        dst->x = v1->x * v2->x;
        dst->y = v1->y * v2->y;
}

static inline void libs_vec2f_scale(struct libs_vec2f *dst, float val)
{
        dst->x *= val;
        dst->y *= val;
}

static inline void libs_vec2i_scale(struct libs_vec2i *dst, float val)
{
        dst->x *= val;
        dst->y *= val;
}

static inline void libs_vec2f_div(struct libs_vec2f *dst,
                                  const struct libs_vec2f *v1,
                                  const struct libs_vec2f *v2)
{
        dst->x = v1->x / v2->x;
        dst->y = v1->y / v2->y;
}

static inline void libs_vec2i_div(struct libs_vec2i *dst,
                                  const struct libs_vec2i *v1,
                                  const struct libs_vec2i *v2)
{
        dst->x = v1->x / v2->x;
        dst->y = v1->y / v2->y;
}

static inline float libs_vec2f_length(const struct libs_vec2f *v)
{
        return sqrtf(powf(v->x, 2) + powf(v->y, 2));
}

static inline float libs_vec2i_length(const struct libs_vec2i *v)
{
        return sqrtf(powf(v->x, 2) + powf(v->y, 2));
}

static inline float libs_vec2f_dist(const struct libs_vec2f *v1,
                                    const struct libs_vec2f *v2)
{
        struct libs_vec2f tmp;
        libs_vec2f_sub(&tmp, v1, v2);
        return libs_vec2f_length(&tmp);
}

static inline float libs_vec2i_dist(const struct libs_vec2i *v1,
                                    const struct libs_vec2i *v2)
{
        struct libs_vec2i tmp;
        libs_vec2i_sub(&tmp, v1, v2);
        return libs_vec2i_length(&tmp);
}

static inline float libs_vec2f_dot(const struct libs_vec2f* v1,
                                   const struct libs_vec2f* v2)
{
        return v1->x * v2->x + v1->y * v2->y;
}

static inline void libs_vec2f_perp(struct libs_vec2f* out,
                                   const struct libs_vec2f* v)
{
        out->x = v->y;
        out->y = v->x * -1;
}

static inline float libs_vec2i_dot(const struct libs_vec2i* v1,
                                   const struct libs_vec2i* v2)
{
        return v1->x * v2->x + v1->y * v2->y;
}

static inline void libs_vec2i_perp(struct libs_vec2i* out,
                                   const struct libs_vec2i* v)
{
        out->x = v->y;
        out->y = v->x * -1;
}

static inline bool libs_vec2f_colinear(const struct libs_vec2f *v1,
                                       const struct libs_vec2f *v2)
{
        int x1 = v1->x, y1 = v1->y, x2 = v2->x, y2 = v2->y;
        float modx = (v1->x > v2->x) ? x1 % x2 : x2 % x1;
        float mody = (v1->y > v2->y) ? y1 % y2 : y2 % y1;
        if (modx + mody == 0) {
                return v1->x / v2->x == v1->y / v2->y;
        }
}
#endif /* Header guard */
