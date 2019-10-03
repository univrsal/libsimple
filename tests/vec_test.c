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
#include "test.h"
#include "vec.h"

void vec_test(void)
{
    BEGIN_TEST("vector");
    struct libs_vec *v1 = libs_vector(libs_vec_2f, 2.5f, 3.5f);
    struct libs_vec *v2 = libs_vector(libs_vec_2f, 1.1, 1.1);
    struct libs_vec2f *vd = v1->ptr;
    struct libs_vec2f *vd2 = v2->ptr;

    /* Generic vector test */
    libs_vec_set(v1, 5.5, 5.5);
    libs_vec_add(v1, v1, v2);
    libs_vec_set(v2, 2.f, 2.f);
    libs_vec_mul(v1, v1, v2);
    assert(vd->x == 13.2f);
    libs_vector_free(v1);
    libs_vector_free(v2);

    /* Specific vectors */
    struct libs_vec2f v2f = { 2.5f, 2.5f };
    struct libs_vec2i v2i = { 5, 5 };

    struct libs_vec2i perp2i;
    struct libs_vec2f perp2f;

    /* 2D */
    libs_vec2f_add(&v2f, &v2f, &v2f);
    libs_vec2f_mul(&v2f, &v2f, &v2f);
    libs_vec2f_div(&v2f, &v2f, &v2f);
    assert(v2f.x == 1.f);

    libs_vec2f_perp(&perp2f, &v2f);
    assert(libs_vec2f_dot(&perp2f, &v2f) == 0);

    libs_vec2i_add(&v2i, &v2i, &v2i);
    libs_vec2i_mul(&v2i, &v2i, &v2i);
    libs_vec2i_div(&v2i, &v2i, &v2i);
    assert(v2i.x == 1);

    libs_vec2i_perp(&perp2i, &v2i);
    assert(libs_vec2i_dot(&perp2i, &v2i) == 0);

    /* 3D */
    struct libs_vec3f v3f = { 2.5f, 2.5f, 2.5f };
    struct libs_vec3f v3f2 = { 1.f, 1.f, 1.f };
    struct libs_vec3i v3i = { 5, 5, 5 };
    struct libs_vec3i v3i2 = { 1, 1, 1 };

    struct libs_vec3i perp3i;
    struct libs_vec3f perp3f;
    libs_vec3f_add(&v3f, &v3f, &v3f);
    libs_vec3f_mul(&v3f, &v3f, &v3f);
    libs_vec3f_div(&v3f, &v3f, &v3f);
    assert(v3f.x == 1.f);

    libs_vec3f_perp(&perp3f, &v3f, &v3f2);
    assert(libs_vec3f_dot(&perp3f, &v3f) == 0.f);

    libs_vec2i_add(&v2i, &v2i, &v2i);
    libs_vec2i_mul(&v2i, &v2i, &v2i);
    libs_vec2i_div(&v2i, &v2i, &v2i);
    assert(v2i.x == 1);

    libs_vec2i_perp(&perp3i, &v2i);
    assert(libs_vec2i_dot(&perp3i, &v2i) == 0);
}
