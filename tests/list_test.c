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
#include <assert.h>
#include <libsimple.h>

void list_test(void)
{
        BEGIN_TEST("list");
        struct libs_list *list = libs_list();
        assert(list);
        for (int8_t i = 0; i < 10; i++)
                libs_list_append_int8(list, i);

        size_t index;
        struct libs_list_node *node;
        int8_t* data;
        libs_list_foreach(list, index, node) {
            data = libs_list_node_data(node, NULL);
            assert(*data == index);
        };

        assert(libs_list_size(list) == 10);
        assert(* (int8_t*)libs_list_at(list, 9) == 9);
        libs_list_destroy(list);
}
