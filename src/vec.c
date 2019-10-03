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
#include "vec.h"
#include <assert.h>

void libs_vec_set(struct libs_vec *v, ...)
{
    va_list l;
    va_start(l, v);
    if (v->t == libs_vec_2f) {
        struct libs_vec2f *tmp = v->ptr;
        tmp->x = va_arg(l, double);
        tmp->y = va_arg(l, double);
    } else if (v->t == libs_vec_2i) {
        struct libs_vec2i *tmp = v->ptr;
        tmp->x = va_arg(l, int);
        tmp->y = va_arg(l, int);
    } else if (v->t == libs_vec_3f) {
        struct libs_vec3f *tmp = v->ptr;
        tmp->x = va_arg(l, double);
        tmp->y = va_arg(l, double);
        tmp->z = va_arg(l, double);
    } else if (v->t == libs_vec_3i) {
        struct libs_vec3i *tmp = v->ptr;
        tmp->x = va_arg(l, int);
        tmp->y = va_arg(l, int);
        tmp->z = va_arg(l, int);
    } else if (v->t == libs_vec_4f) {
        struct libs_vec4f *tmp = v->ptr;
        tmp->x = va_arg(l, double);
        tmp->y = va_arg(l, double);
        tmp->z = va_arg(l, double);
        tmp->w = va_arg(l, double);
    } else if (v->t == libs_vec_4i) {
        struct libs_vec4i *tmp = v->ptr;
        tmp->x = va_arg(l, int);
        tmp->y = va_arg(l, int);
        tmp->z = va_arg(l, int);
        tmp->w = va_arg(l, int);
    }
    va_end(l);
}

void libs_vec_add2(struct libs_vec *dst, const struct libs_vec *v1,
                  const struct libs_vec *v2, int8_t sign)
{
    assert(libs_vec_type_equal(dst, v1) && libs_vec_type_equal(v1, v2));

    if (dst->t == libs_vec_2f) {
        struct libs_vec2f* tmp = dst->ptr;
        struct libs_vec2f* a = v1->ptr;
        struct libs_vec2f* b = v2->ptr;
        tmp->x = a->x + (b->x * sign);
        tmp->y = a->y + (b->y * sign);
    } else if (dst->t == libs_vec_2i) {
        struct libs_vec2i* tmp = dst->ptr;
        struct libs_vec2i* a = v1->ptr;
        struct libs_vec2i* b = v2->ptr;
        tmp->x = a->x + (b->x * sign);
        tmp->y = a->y + (b->y * sign);
    } else if (dst->t == libs_vec_3f) {
        struct libs_vec3f* tmp = dst->ptr;
        struct libs_vec3f* a = v1->ptr;
        struct libs_vec3f* b = v2->ptr;
        tmp->x = a->x + (b->x * sign);
        tmp->y = a->y + (b->y * sign);
        tmp->z = a->z + (b->z * sign);
    } else if (dst->t == libs_vec_3i) {
        struct libs_vec3i* tmp = dst->ptr;
        struct libs_vec3i* a = v1->ptr;
        struct libs_vec3i* b = v2->ptr;
        tmp->x = a->x + (b->x * sign);
        tmp->y = a->y + (b->y * sign);
        tmp->z = a->z + (b->z * sign);
    } else if (dst->t == libs_vec_4f) {
        struct libs_vec4f* tmp = dst->ptr;
        struct libs_vec4f* a = v1->ptr;
        struct libs_vec4f* b = v2->ptr;
        tmp->x = a->x + (b->x * sign);
        tmp->y = a->y + (b->y * sign);
        tmp->z = a->z + (b->z * sign);
        tmp->w = a->w + (b->w * sign);
    } else if (dst->t == libs_vec_4i) {
        struct libs_vec4i* tmp = dst->ptr;
        struct libs_vec4i* a = v1->ptr;
        struct libs_vec4i* b = v2->ptr;
        tmp->x = a->x + (b->x * sign);
        tmp->y = a->y + (b->y * sign);
        tmp->z = a->z + (b->z * sign);
        tmp->w = a->w + (b->w * sign);
    }
}

void libs_vec_add(struct libs_vec *dst, const struct libs_vec *v1,
                  const struct libs_vec *v2)
{
    libs_vec_add2(dst, v1, v2, 1);
}

void libs_vec_sub(struct libs_vec *dst, const struct libs_vec *v1,
                  const struct libs_vec *v2)
{
    libs_vec_add2(dst, v1, v2, -1);
}

struct libs_vec *libs_vector(enum libs_vec_type t, ...)
{
    struct libs_vec *new = malloc(sizeof(struct libs_vec));
    new->t = t;
    va_list l;
    va_start(l, t);
    if (t == libs_vec_2f) {
        struct libs_vec2f* tmp = malloc(sizeof(struct libs_vec2f));
        tmp->x = va_arg(l, double);
        tmp->y = va_arg(l, double);
        new->ptr = tmp;
    } else if (t == libs_vec_2i) {
        struct libs_vec2i* tmp = malloc(sizeof(struct libs_vec2i));
        tmp->x = va_arg(l, int);
        tmp->y = va_arg(l, int);
        new->ptr = tmp;
    } else if (t == libs_vec_3f) {
        struct libs_vec3f* tmp = malloc(sizeof(struct libs_vec3f));
        tmp->x = va_arg(l, double);
        tmp->y = va_arg(l, double);
        tmp->z = va_arg(l, double);
        new->ptr = tmp;
    } else if (t == libs_vec_3i) {
        struct libs_vec3i* tmp = malloc(sizeof(struct libs_vec3i));
        tmp->x = va_arg(l, int);
        tmp->y = va_arg(l, int);
        tmp->z = va_arg(l, int);
        new->ptr = tmp;
    } else if (t == libs_vec_4f) {
        struct libs_vec4f* tmp = malloc(sizeof(struct libs_vec4f));
        tmp->x = va_arg(l, double);
        tmp->y = va_arg(l, double);
        tmp->z = va_arg(l, double);
        tmp->w = va_arg(l, double);
        new->ptr = tmp;
    } else if (t == libs_vec_4i) {
        struct libs_vec4i* tmp = malloc(sizeof(struct libs_vec4i));
        tmp->x = va_arg(l, int);
        tmp->y = va_arg(l, int);
        tmp->z = va_arg(l, int);
        tmp->w = va_arg(l, int);
        new->ptr = tmp;
    }
    va_end(l);
    return new;
}

void libs_vec_mul(struct libs_vec *dst, const struct libs_vec *v1,
                  const struct libs_vec *v2)
{
    assert(libs_vec_type_equal(dst, v1) && libs_vec_type_equal(v1, v2));

    if (dst->t == libs_vec_2f) {
        struct libs_vec2f* tmp = dst->ptr;
        struct libs_vec2f* a = v1->ptr;
        struct libs_vec2f* b = v2->ptr;
        tmp->x = a->x * b->x;
        tmp->y = a->y * b->y;
    } else if (dst->t == libs_vec_2i) {
        struct libs_vec2i* tmp = dst->ptr;
        struct libs_vec2i* a = v1->ptr;
        struct libs_vec2i* b = v2->ptr;
        tmp->x = a->x * b->x;
        tmp->y = a->y * b->y;
    } else if (dst->t == libs_vec_3f) {
        struct libs_vec3f* tmp = dst->ptr;
        struct libs_vec3f* a = v1->ptr;
        struct libs_vec3f* b = v2->ptr;
        tmp->x = a->x * b->x;
        tmp->y = a->y * b->y;
        tmp->z = a->z * b->z;
    } else if (dst->t == libs_vec_3i) {
        struct libs_vec3i* tmp = dst->ptr;
        struct libs_vec3i* a = v1->ptr;
        struct libs_vec3i* b = v2->ptr;
        tmp->x = a->x * b->x;
        tmp->y = a->y * b->y;
        tmp->z = a->z * b->z;
    } else if (dst->t == libs_vec_4f) {
        struct libs_vec4f* tmp = dst->ptr;
        struct libs_vec4f* a = v1->ptr;
        struct libs_vec4f* b = v2->ptr;
        tmp->x = a->x * b->x;
        tmp->y = a->y * b->y;
        tmp->z = a->z * b->z;
        tmp->w = a->w * b->w;
    } else if (dst->t == libs_vec_4i) {
        struct libs_vec4i* tmp = dst->ptr;
        struct libs_vec4i* a = v1->ptr;
        struct libs_vec4i* b = v2->ptr;
        tmp->x = a->x * b->x;
        tmp->y = a->y * b->y;
        tmp->z = a->z * b->z;
        tmp->w = a->w * b->w;
    }
}

void libs_vec_div(struct libs_vec *dst, const struct libs_vec *v1,
                  const struct libs_vec *v2)
{
    assert(libs_vec_type_equal(dst, v1) && libs_vec_type_equal(v1, v2));

    if (dst->t == libs_vec_2f) {
        struct libs_vec2f* tmp = dst->ptr;
        struct libs_vec2f* a = v1->ptr;
        struct libs_vec2f* b = v2->ptr;
        tmp->x = a->x / b->x;
        tmp->y = a->y / b->y;
    } else if (dst->t == libs_vec_2i) {
        struct libs_vec2i* tmp = dst->ptr;
        struct libs_vec2i* a = v1->ptr;
        struct libs_vec2i* b = v2->ptr;
        tmp->x = a->x / b->x;
        tmp->y = a->y / b->y;
    } else if (dst->t == libs_vec_3f) {
        struct libs_vec3f* tmp = dst->ptr;
        struct libs_vec3f* a = v1->ptr;
        struct libs_vec3f* b = v2->ptr;
        tmp->x = a->x / b->x;
        tmp->y = a->y / b->y;
        tmp->z = a->z / b->z;
    } else if (dst->t == libs_vec_3i) {
        struct libs_vec3i* tmp = dst->ptr;
        struct libs_vec3i* a = v1->ptr;
        struct libs_vec3i* b = v2->ptr;
        tmp->x = a->x / b->x;
        tmp->y = a->y / b->y;
        tmp->z = a->z / b->z;
    } else if (dst->t == libs_vec_4f) {
        struct libs_vec4f* tmp = dst->ptr;
        struct libs_vec4f* a = v1->ptr;
        struct libs_vec4f* b = v2->ptr;
        tmp->x = a->x / b->x;
        tmp->y = a->y / b->y;
        tmp->z = a->z / b->z;
        tmp->w = a->w / b->w;
    } else if (dst->t == libs_vec_4i) {
        struct libs_vec4i* tmp = dst->ptr;
        struct libs_vec4i* a = v1->ptr;
        struct libs_vec4i* b = v2->ptr;
        tmp->x = a->x / b->x;
        tmp->y = a->y / b->y;
        tmp->z = a->z / b->z;
        tmp->w = a->w / b->w;
    }
}
