/* Copyright (c) 2020 github.com/univrsal <universailp@web.de>
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

#include "buffer.h"
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

struct libs_buffer {
    size_t size;
    size_t write_pos;
    size_t read_pos;
    void *data;
};

struct libs_buffer *libs_buffer(size_t size)
{
    struct libs_buffer *buf = malloc(sizeof(struct libs_buffer));
    buf->size = size;
    buf->data = malloc(size);
    buf->write_pos = 0;
    buf->read_pos = 0;
    memset(buf->data, 0, size);
    return buf;
}

size_t libs_buffer_size(const struct libs_buffer *buf)
{
    if (buf)
        return buf->size;
    return 0;
}
