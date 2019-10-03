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
#ifndef LIB_SIMPLE_VEC3
#define LIB_SIMPLE_VEC3
#include <math.h>

struct libs_vec3f {
        union {
                struct { float x, y, z; };
                float p[3];
        };
};

struct libs_vec3i {
        union {
                struct { int x, y, z; };
                int p[3];
        };
};

static inline void libs_vec3f_zero(struct libs_vec3f *v)
{
        v->x = 0.f;
        v->y = 0.f;
        v->z = 0.f;
}

static inline void libs_vec3i_zero(struct libs_vec3i *v)
{
       v->x = 0;
       v->y = 0;
       v->z = 0;
}

static inline void libs_vec3f_set(struct libs_vec3f *v, float x, float y, float z)
{
        v->x = x;
        v->y = y;
        v->z = z;
}

static inline void libs_vec3i_set(struct libs_vec3f *v, int x, int y, int z)
{
        v->x = x;
        v->y = y;
        v->z = z;
}

static inline void libs_vec3f_add(struct libs_vec3f *dst,
                                  const struct libs_vec3f *v1,
                                  const struct libs_vec3f *v2)
{
        dst->x = v1->x + v2->x;
        dst->y = v1->y + v2->y;
        dst->z = v1->z + v2->z;
}

static inline void libs_vec3i_add(struct libs_vec3i *dst,
                                  const struct libs_vec3i *v1,
                                  const struct libs_vec3i *v2)
{
        dst->x = v1->x + v2->x;
        dst->y = v1->y + v2->y;
        dst->z = v1->z + v2->z;
}

static inline void libs_vec3f_sub(struct libs_vec3f *dst,
                                  const struct libs_vec3f *v1,
                                  const struct libs_vec3f *v2)
{
        dst->x = v1->x - v2->x;
        dst->y = v1->y - v2->y;
        dst->z = v1->z - v2->z;
}

static inline void libs_vec3i_sub(struct libs_vec3i *dst,
                                  const struct libs_vec3i *v1,
                                  const struct libs_vec3i *v2)
{
        dst->x = v1->x - v2->x;
        dst->y = v1->y - v2->y;
        dst->z = v1->z - v2->z;
}

static inline void libs_vec3f_mul(struct libs_vec3f *dst,
                                  const struct libs_vec3f *v1,
                                  const struct libs_vec3f *v2)
{
        dst->x = v1->x * v2->x;
        dst->y = v1->y * v2->y;
        dst->z = v1->z * v2->z;
}

static inline void libs_vec3i_mul(struct libs_vec3i *dst,
                                  const struct libs_vec3i *v1,
                                  const struct libs_vec3i *v2)
{
        dst->x = v1->x * v2->x;
        dst->y = v1->y * v2->y;
        dst->z = v1->z * v2->z;
}

static inline void libs_vec3f_scale(struct libs_vec3f *dst, float val)
{
        dst->x *= val;
        dst->y *= val;
        dst->z *= val;
}

static inline void libs_vec3i_scale(struct libs_vec3i *dst, float val)
{
        dst->x *= val;
        dst->y *= val;
        dst->z *= val;
}

static inline void libs_vec3f_div(struct libs_vec3f *dst,
                                  const struct libs_vec3f *v1,
                                  const struct libs_vec3f *v2)
{
        dst->x = v1->x / v2->x;
        dst->y = v1->y / v2->y;
        dst->z = v1->z / v2->z;
}

static inline void libs_vec3i_div(struct libs_vec3i *dst,
                                  const struct libs_vec3i *v1,
                                  const struct libs_vec3i *v2)
{
        dst->x = v1->x / v2->x;
        dst->y = v1->y / v2->y;
        dst->z = v1->z / v2->z;
}

static inline float libs_vec3f_length(const struct libs_vec3f *v)
{
        return sqrtf(powf(v->x, 2) + powf(v->y, 2) + powf(v->z, 2));
}

static inline float libs_vec3i_length(const struct libs_vec3i *v)
{
        return sqrtf(powf(v->x, 2) + powf(v->y, 2) + powf(v->z, 2));
}

static inline float libs_vec3f_dist(const struct libs_vec3f *v1,
                                    const struct libs_vec3f *v2)
{
        struct libs_vec3f tmp;
        libs_vec3f_sub(&tmp, v1, v2);
        return libs_vec3f_length(&tmp);
}

static inline float libs_vec3i_dist(const struct libs_vec3i *v1,
                                    const struct libs_vec3i *v2)
{
        struct libs_vec3i tmp;
        libs_vec3i_sub(&tmp, v1, v2);
        return libs_vec3i_length(&tmp);
}

static inline float libs_vec3f_dot(const struct libs_vec3f* v1,
                                   const struct libs_vec3f* v2)
{
        return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

static inline void libs_vec3f_perp(struct libs_vec3f* out,
                                   const struct libs_vec3f* v1,
                                   const struct libs_vec3f* v2)
{
        out->x = v1->y * v2->z - v1->z * v2->y;
        out->y = v1->z * v2->x - v1->x * v2->z;
        out->z = v1->x * v2->y - v1->y * v2->x;
}

static inline float libs_vec3i_dot(const struct libs_vec3i* v1,
                                   const struct libs_vec3i* v2)
{
        return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

static inline void libs_vec3i_perp(struct libs_vec3i* out,
                                   const struct libs_vec3i* v1,
                                   const struct libs_vec3i* v2)
{
        out->x = v1->y * v2->z - v1->z * v2->y;
        out->y = v1->z * v2->x - v1->x * v2->z;
        out->z = v1->x * v2->y - v1->y * v2->x;
}
#endif /* Header guard */
