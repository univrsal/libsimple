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

#ifndef LIB_SIMPLE_BUFFER_H
#define LIB_SIMPLE_BUFFER_H
#include "types.h"

/**
  * \struct libs_buffer
  * \brief Simple byte buffer
  * that can be written to
  * either directly or with
  * helper methods
  */
struct libs_buffer;
#ifdef LIB_SIMPLE_TYPEDEF
typedef struct libs_buffer libs_buffer_t;
#endif

/**
  * \brief Create a buffer of provided size
  * data is zeroed
  * \param size	size of buffer
  * \return		pointer to buffer structure
  */
extern DECLSPEC struct libs_buffer *LIBS_CALL
libs_buffer(size_t size);

/** \brief Returns the memory size of the buffer
  * \param buf	the buffer
  * \return		the total size of the buffer in bytes
  */
extern DECLSPEC size_t LIBS_CALL
libs_buffer_size(const struct libs_buffer *buf);

/** \brief Resizes the buffer of the buffer
  * \param buf	the buffer
  * \return		the total size of the buffer in bytes
  */
extern DECLSPEC size_t LIBS_CALL
libs_buffer_size(const struct libs_buffer *buf);

/** \brief Write a data chunk to the buffer
  * \param buf	the buffer
  * \param data	the data
  * \param size	the size of data
  * \return 	true if the data fit into the buffer
  */
extern DECLSPEC bool LIBS_CALL
libs_buffer_write(struct libs_buffer *buf, const void *data,
                  size_t size);
#endif
