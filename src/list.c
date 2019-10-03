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
#include "list.h"
#include <malloc.h>
#include <memory.h>

struct libs_list_node {
    struct libs_list_node *prev;
    struct libs_list_node *next;
    void *data;
    size_t data_size;
};

struct libs_list {
    size_t count;
    struct libs_list_node *first;
    struct libs_list_node *last;
};

struct libs_list *libs_list(void)
{
    struct libs_list *new = malloc(sizeof(struct libs_list));
    if (!new) return NULL;
    new->last = NULL;
    new->first = NULL;
    new->count = 0;
    return new;
}

void libs_list_destroy(struct libs_list *list)
{
    if (list->count > 0) {
        struct libs_list_node *curr = list->first, *tmp;
        while (curr) {
            tmp = curr->next;
            free(curr->data);
            free(curr);
            curr = tmp;
        }
    }
    free(list);
}

/* Only frees memory */
void delete_node(struct libs_list_node *node)
{
    free(node->data);
    free(node);
}

struct libs_list_node *new_node(void *data, size_t size)
{
    if (!data || size == 0)
        return NULL;
    struct libs_list_node *new = malloc(sizeof(struct libs_list_node));
    new->data = malloc(size);
    new->data = memcpy(new->data, data, size);
    new->data_size = size;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

void libs_list_append(struct libs_list *list, void *data, size_t size)
{
    struct libs_list_node *new = new_node(data, size);
    if (!new) return;
    new->prev = list->last;
    if (list->last)
        list->last->next = new;
    list->last = new;
    if (!list->first)
        list->first = new;
    list->count++;
}

void libs_list_append_int8(struct libs_list *list, int8_t i)
{
    libs_list_append(list, &i, sizeof(int8_t));
}

void libs_list_append_int16(struct libs_list *list, int16_t i)
{
    libs_list_append(list, &i, sizeof(int16_t));
}

void libs_list_append_int32(struct libs_list *list, int32_t i)
{
    libs_list_append(list, &i, sizeof(int32_t));
}

void libs_list_append_int64(struct libs_list *list, int64_t i)
{
    libs_list_append(list, &i, sizeof(int64_t));
}

void libs_list_prepend(struct libs_list *list, void *data, size_t size)
{
    struct libs_list_node *new = new_node(data, size);
    if (!new) return;
    new->next = list->first;
    list->first = new;
    if (!list->last)
        list->last = new;
    list->count++;
}

void libs_list_prepend_int8(struct libs_list *list, int8_t i)
{
    libs_list_prepend(list, &i, sizeof(int8_t));
}

void libs_list_prepend_int16(struct libs_list *list, int16_t i)
{
    libs_list_prepend(list, &i, sizeof(int16_t));
}

void libs_list_prepend_int32(struct libs_list *list, int32_t i)
{
    libs_list_prepend(list, &i, sizeof(int32_t));
}

void libs_list_prepend_int64(struct libs_list *list, int64_t i)
{
    libs_list_prepend(list, &i, sizeof(int64_t));
}

/* Internal only */
struct libs_list_node *node_at(struct libs_list *list, size_t at)
{
    if (at >= list->count)
        return NULL;
    struct libs_list_node *curr = NULL;
    size_t index = 0;
    if (at > list->count / 2) { /* Count down */
        curr = list->last;
        index = list->count - 1;
        while (curr && index > at) {
            if (curr->prev)
                curr = curr->prev;
            else
                break;
            index--;
        }
    } else { /* Count up */
        curr = list->first;
        while (curr && index < at) {
            if (curr->next)
                curr = curr->next;
            else
                break;
            index++;
        }
    }

    return curr;
}

void *libs_list_at(struct libs_list *list, size_t at)
{
    void *data = NULL;
    struct libs_list_node *node = node_at(list, at);
    if (node)
        data = node->data;
    return data;
}


void libs_list_insert(struct libs_list *list, void *data, size_t size,
              size_t at)
{
    struct libs_list_node *node = node_at(list, at);
    if (node) {
        struct libs_list_node *new = new_node(data, size);
        if (!new) return;
        struct libs_list_node *old_next = node->next;
        node->next = new;
        new->prev = node;
        new->next = old_next;
    }
}

void libs_list_insert_int8(struct libs_list *list, int8_t i, size_t at)
{
    libs_list_insert(list, &i, sizeof(int8_t), at);
}

void libs_list_insert_int16(struct libs_list *list, int16_t i, size_t at)
{
    libs_list_insert(list, &i, sizeof(int16_t), at);
}

void libs_list_insert_int32(struct libs_list *list, int32_t i, size_t at)
{
    libs_list_insert(list, &i, sizeof(int32_t), at);
}

void libs_list_insert_int64(struct libs_list *list, int64_t i, size_t at)
{
    libs_list_insert(list, &i, sizeof(int64_t), at);
}

void libs_list_delete(struct libs_list *list, size_t at)
{
    struct libs_list_node *node = node_at(list, at);
    if (!node) return;

    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    delete_node(node);
}

size_t libs_list_size(struct libs_list *list)
{
    return list->count;
}

void *libs_list_first(struct libs_list *list)
{
    if (list->first)
        return list->first->data;
    return NULL;
}

struct libs_list_node *libs_list_first_node(struct libs_list *list)
{
    if (list->first)
        return list->first;
    return NULL;
}

void *libs_list_last(struct libs_list *list)
{
    if (list->last)
        return list->last->data;
    return NULL;
}

struct libs_list_node *libs_list_last_node(struct libs_list *list)
{
    if (list->last)
        return list->last;
    return NULL;
}

struct libs_list_node *libs_list_node_next(struct libs_list_node *node)
{
    if (node)
        return node->next;
    return NULL;
}

struct libs_list_node *libs_list_node_prev(struct libs_list_node *node)
{
    if (node)
        return node->prev;
    return NULL;
}

void *libs_list_node_data(struct libs_list_node *node, size_t* size)
{
    if (node) {
        if (size)
            *size = node->data_size;
        return node->data;
    }
    return NULL;
}
