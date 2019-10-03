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
#ifndef LIB_SIMPLE_LIST_H
#define LIB_SIMPLE_LIST_H
#include "types.h"

struct libs_list;

struct libs_list_node;

#ifdef LIB_SIMPLE_TYPEDEF
typedef struct libs_list libs_list_t;
typedef struct libs_list_node list_list_node_t;
#endif

/* Creates an empty list */
extern DECLSPEC struct libs_list *LIBS_CALL
libs_list(void);

/* Frees all memory allocated by the list */
extern DECLSPEC void LIBS_CALL
libs_list_destroy(struct libs_list *list);

/* Append a new item to the end */
extern DECLSPEC void LIBS_CALL
libs_list_append(struct libs_list *list, void *data, size_t size);

/* Boiler plate for primitive types */
extern DECLSPEC void LIBS_CALL
libs_list_append_int8(struct libs_list *list, int8_t i);

extern DECLSPEC void LIBS_CALL
libs_list_append_int16(struct libs_list *list, int16_t i);

extern DECLSPEC void LIBS_CALL
libs_list_append_int32(struct libs_list *list, int32_t i);

extern DECLSPEC void LIBS_CALL
libs_list_append_int64(struct libs_list *list, int64_t i);

/* Unsigned/Signed can be cast */
#define libs_list_append_uint8(l, i) libs_list_append_int8(l, (int8_t) i)
#define libs_list_append_char(l, c) libs_list_append_int8(l, (int8_t) c)
#define libs_list_append_uint16(l, i) libs_list_append_int16(l, (int16_t) i)
#define libs_list_append_uint32(l, i) libs_list_append_int32(l, (int32_t) i)
#define libs_list_append_uint64(l, i) libs_list_append_int64(l, (int64_t) i)

/* Adds an item to the beginning of the list
 * aka the index 0
 */
extern DECLSPEC void LIBS_CALL
libs_list_prepend(struct libs_list *list, void *data, size_t size);

/* Boiler plate for primitive types */
extern DECLSPEC void LIBS_CALL
libs_list_prepend_int8(struct libs_list *list, int8_t i);

extern DECLSPEC void LIBS_CALL
libs_list_prepend_int16(struct libs_list *list, int16_t i);

extern DECLSPEC void LIBS_CALL
libs_list_prepend_int32(struct libs_list *list, int32_t i);

extern DECLSPEC void LIBS_CALL
libs_list_prepend_int64(struct libs_list *list, int64_t i);

 /* Unsigned/Signed can be cast */
#define libs_list_prepend_uint8(l, i) libs_list_prepend_int8(l, (int8_t) i)
#define libs_list_prepend_char(l, c) libs_list_prepend_int8(l, (int8_t) c)
#define libs_list_prepend_uint16(l, i) libs_list_prepend_int16(l, (int16_t) i)
#define libs_list_prepend_uint32(l, i) libs_list_prepend_int32(l, (int32_t) i)
#define libs_list_prepend_uint64(l, i) libs_list_prepend_int64(l, (int64_t) i)

/* Returns the data of the item at the provided index */
extern DECLSPEC void *LIBS_CALL
libs_list_at(struct libs_list *list, size_t at);

/* Inserts an item at the provided index */
extern DECLSPEC void LIBS_CALL
libs_list_insert(struct libs_list *list, void *data, size_t size, size_t at);

/* Boiler plate for primitive types */
extern DECLSPEC void LIBS_CALL
libs_list_insert_int8(struct libs_list *list, int8_t i, size_t at);

extern DECLSPEC void LIBS_CALL
libs_list_insert_int16(struct libs_list *list, int16_t i, size_t at);

extern DECLSPEC void LIBS_CALL
libs_list_insert_int32(struct libs_list *list, int32_t i, size_t at);

extern DECLSPEC void LIBS_CALL
libs_list_insert_int64(struct libs_list *list, int64_t i, size_t at);

/* Unsigned/Signed can be cast */
#define libs_list_insert_uint8(l, i, a) libs_list_insert_int8(l, (int8_t) i, a)
#define libs_list_insert_char(l, c, a) libs_list_insert_int8(l, (int8_t) c, a)
#define libs_list_insert_uint16(l, i, a) libs_list_insert_int16(l, (int16_t) i, a)
#define libs_list_insert_uint32(l, i, a) libs_list_insert_int32(l, (int32_t) i, a)
#define libs_list_insert_uint64(l, i, a) libs_list_insert_int64(l, (int64_t) i, a)

/* Delets an item at the provided index */
extern DECLSPEC void LIBS_CALL
libs_list_delete(struct libs_list *list, size_t at);

/* Returns the amount of items in the list */
extern DECLSPEC size_t LIBS_CALL
libs_list_size(struct libs_list *list);

/* Returns the first item in the list
 * aka the item which would be in
 * index 0 in an array
 */
extern DECLSPEC void *LIBS_CALL
libs_list_first(struct libs_list *list);

/* Returns first the node, which contains next, previous
 * and data pointer. NULL if list is empty */
extern DECLSPEC struct libs_list_node *LIBS_CALL
libs_list_first_node(struct libs_list *list);

/* Returns the last item in the list
 * aka the item which would be in
 * index n - 1 in an array of length n
 */
extern DECLSPEC void *LIBS_CALL
libs_list_last(struct libs_list *list);

/* Returns last the node, which contains next, previous
 * and data pointer. NULL if list is empty */
extern DECLSPEC struct libs_list_node *LIBS_CALL
libs_list_last_node(struct libs_list *list);

/* Access methods for list node */
extern DECLSPEC struct libs_list_node *LIBS_CALL
libs_list_node_next(struct libs_list_node *node);

extern DECLSPEC struct libs_list_node *LIBS_CALL
libs_list_node_prev(struct libs_list_node *node);

/* If size is not NULL size of the data held by the node
 * will be stored in there */
extern DECLSPEC void *LIBS_CALL
libs_list_node_data(struct libs_list_node *node, size_t* size);

#define libs_list_foreach(list, index, node) for (index = 0,\
    node = libs_list_first_node(list);\
    node; ++index, node = libs_list_node_next(node))
#endif /* Header guard */
