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
#include "str.h"
#include <string.h>
#include <wchar.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
#ifdef _WIN32
#include <Windows.h>
#endif

/* Byte offset between struct head and string pointer */
static int str_offset = 0;

struct libs_string
{
        size_t len;		/* Length		*/
        enum libs_str_type enc;	/* Encoding		*/
        void *str;		/* Actual string 	*/
};

char **libs_string(const char* str)
{
    struct libs_string *new_str = malloc(sizeof(struct libs_string));
    new_str->len = strlen(str);
    new_str->enc = libs_utf8;
    new_str->str = strdup(str);

    if (str_offset == 0)
        str_offset = (int) &new_str->str - (int) new_str;

    /* Intentionally return pointer to string
     * so C String manipulation can directly use it
     */
    return (char**) &new_str->str;
}

wchar_t **libs_wstring(const wchar_t* wstr)
{
    struct libs_string *new_str = malloc(sizeof(struct libs_string));
    new_str->len = wcslen(wstr);
    new_str->enc = libs_utf16;
    new_str->str = wcsdup(wstr);

    if (str_offset == 0)
        str_offset = (int) &new_str->str - (int) new_str;
    return (wchar_t **) &new_str->str;
}

/* Internal utility */
struct libs_string *libs_string_get(void *str)
{
    assert(str_offset > 0);
    assert(str);
    str -= str_offset;
    return (struct libs_string *) str;
}

const struct libs_string *libs_string_cget(const void *str)
{
    assert(str_offset > 0);
    str -= str_offset;
    return (const struct libs_string *) str;
}
/* ==== */

void libs_string_destroy(void *str)
{
    struct libs_string *s = libs_string_get(str);
    free(s->str);
    free(s);
}

bool libs_string_wcs_to_utf8(void *str)
{
    bool result = true;
    if (!str) return false;
    struct libs_string *s = libs_string_get(str);
    if (s->enc == libs_utf8) return true;

    size_t wcs_len = wcslen(str + 1);
    char* new_str = NULL;
#ifdef _WIN32
    size_t space_req = WideCharToMultiByte(CP_UTF8, 0, str, wcs_len,
                           NULL, 0, NULL, NULL);
    if (space_req > 0) {
        new_str = malloc(sizeof(char) * space_required);
        assert(new_str);
        WideCharToMultiByte(CP_UTF8, 0, str, wcs_len, new_str,
                    space_required, NULL, NULL);
    } else {
        result = false;
    }
#elif LINUX
    size_t space_req = wcstombs(NULL, str, wcs_len);
    if (space_req > 0) {
        new_str = malloc(sizeof(char) * space_req);
        assert(new_str);
        wcstombs(new_str, str, space_req);
    } else {
        result = false;
    }
#endif
    if (result) {
        free(s->str);
        s->str = new_str;
        s->len = wcs_len;
        s->enc = libs_utf8;
    }

    return result;
}

bool libs_string_utf8_to_wcs(void *str)
{
    bool result = true;
    if (!str) return false;
    struct libs_string *s = libs_string_get(str);
    if (s->enc == libs_utf16) return true;

    size_t str_len = strlen(str) + 1;
    wchar_t *wstr = NULL;

#ifdef _WIN32
    size_t space_req = MultiByteToWideChar(CP_UTF8, 0, str, str_len,
                           NULL, 0);

    if (space_req > 0) {
        wstr = malloc(space_req * sizeof(wchar_t));
        assert(wstr);
        MultiByteToWideChar(CP_UTF8, 0, str, str_len, wstr, space_req);
    } else {
        result = false;
    }
#elif LINUX
    size_t space_req = mbstowcs(NULL, str, str_len);
    if (space_req > 0) {
        wstr = malloc(space_req * sizeof(wchar_t));
        assert(wstr);
        mbstowcs(wstr, str, space_req);
    } else {
        result = false;
    }
#endif

    if (result) {
        free(s->str);
        s->str = wstr;
        s->len = str_len;
        s->enc = libs_utf16;
    }
    return result;
}

void libs_string_refresh(void *str)
{
    struct libs_string *s = libs_string_get(str);
    if (!s) return;

    if (s->enc == libs_utf8)
        s->len = strlen(s->str);
    else if (s->enc == libs_utf16)
        s->len = wcslen(s->str);
}

int libs_string_replace_char(void *str, char find, char replace)
{
    int found = 0;
    struct libs_string *s = libs_string_get(str);
    char *ptr = s->str;

    if (!s || s->enc != libs_utf8 || !(*ptr))
        return 0;

    do {
        if (*ptr == find) {
            *ptr = replace;
            found++;
        }
    } while (*ptr++);
    return found;
}

int libs_wstring_replace_char(void *str, wchar_t find, wchar_t replace)
{
    int found = 0;
    struct libs_string *s = libs_string_get(str);
    wchar_t *ptr = s->str;

    if (!s || s->enc != libs_utf16 || !(*ptr))
        return 0;

    do {
        if (*ptr == find) {
            *ptr = replace;
            found++;
        }
    } while (*ptr++);
    return found;
}

int libs_string_replace_cstr(void *str, const char *find, const char *replace)
{
    int found = 0;
    struct libs_string *s = libs_string_get(str);
    char *ptr = s->str;

    if (!s || s->enc != libs_utf8 || !(*ptr) || !find || !replace)
        return 0;
    size_t repl_len = strlen(replace);
    size_t find_len = strlen(find);
    int replace_counts = libs_string_count_cstr(str, find);
    /* new length of the string */
    size_t new_len = s->len + 1 + ((repl_len - find_len) * replace_counts);

    /* Make string array bigger, if replacement string needs more space */
    if (find_len < repl_len)
        s->str = realloc(s->str, new_len * sizeof(char));

    while ((ptr = strstr(ptr, find))) {
        /* Null terminator + 1 */
        size_t ptr_len = (strlen(ptr) + 1) * sizeof(char);

        if (find_len > repl_len) { /* Move rest to fill space */
            memmove(ptr + repl_len, ptr + find_len, ptr_len -
                repl_len);
        } else if (find_len < repl_len) { /* Move rest to make space */

            memmove(ptr + repl_len, ptr + find_len, ptr_len -
                find_len);
        }
        /* Replace with new string */
        memcpy(ptr, replace, repl_len);
        found++;
    }

    /* Make string array smaller, if replacement string needs less space */
    if (find_len > repl_len)
        s->str = realloc(s->str, new_len * sizeof(char));

    /* Update string length */
    libs_string_refresh(str);
    return found;
}

int libs_wstring_replace_cstr(void *str, const wchar_t *find, const wchar_t
                  *replace)
{
    int found = 0;
    struct libs_string *s = libs_string_get(str);
    wchar_t *ptr = s->str;

    if (!s || s->enc != libs_utf16 || !(*ptr) || !find || !replace)
        return 0;
    size_t repl_len = wcslen(replace);
    size_t find_len = wcslen(find);
    int replace_counts = libs_wstring_count_cstr(str, find);
    /* new length of the string */
    size_t new_len = s->len + 1 + ((repl_len - find_len) * replace_counts);

    /* Make string array bigger, if replacement string needs more space */
    if (find_len < repl_len) {
        s->str = realloc(s->str, new_len * sizeof(wchar_t));
    }

    while ((ptr = wcsstr(ptr, find))) {
         /* Null terminator + 1 */
        size_t ptr_len = (wcslen(ptr) + 1);
        if (find_len > repl_len) { /* Move rest to fill space */
            memmove(ptr + repl_len, ptr + find_len, (ptr_len -
                repl_len) * sizeof(wchar_t));
        } else if (find_len < repl_len) { /* Move rest to make space */
            memmove(ptr + repl_len, ptr + find_len, (ptr_len -
                find_len) * sizeof(wchar_t));
        }
        /* Replace with new string */
        memcpy(ptr, replace, repl_len * sizeof(wchar_t));
        found++;
    }

    /* Make string array smaller, if replacement string needs less space */
    if (find_len > repl_len) {
        s->str = realloc(s->str, new_len * sizeof (wchar_t));
    }
    /* Update string length */
    libs_string_refresh(str);
    return found;
}

int libs_string_count_char(const void *str, char which)
{
    int found = 0;
    const struct libs_string *s = libs_string_cget(str);

    if (!s || s->enc != libs_utf8 || s->len < 1)
        return 0;
    char *ptr = s->str;
    do {
        if (*ptr == which)
            found++;
    } while (++ptr && strlen(ptr) > 0);
    return found;
}

int libs_wstring_count_char(const void *str, wchar_t which)
{
    int found = 0;
    const struct libs_string *s = libs_string_cget(str);

    if (!s || s->enc != libs_utf16 || s->len < 1)
        return 0;
    wchar_t *ptr = s->str;
    do {
        if (*ptr == which)
            found++;
    } while (++ptr && wcslen(ptr) > 0);
    return found;
}

int libs_string_count_cstr(const void *str, const char *which)
{
    int found = 0;
    const struct libs_string *s = libs_string_cget(str);

    if (!s || s->enc != libs_utf8 || s->len < 1)
        return 0;
    char *ptr = s->str;
    size_t which_len = strlen(which);
    size_t index = 0;
    while (index < s->len && (ptr = strstr(ptr, which))) {
        found++;
        ptr += which_len;
        index += which_len;
    }
    return found;
}

int libs_wstring_count_cstr(const void *str, const wchar_t *which)
{
    int found = 0;
    const struct libs_string *s = libs_string_cget(str);

    if (!s || s->enc != libs_utf16 || s->len < 1)
        return 0;
    wchar_t *ptr = s->str;
    size_t which_len = wcslen(which);
    size_t index = 0;
    while (index < s->len && (ptr = wcsstr(ptr, which))) {
        found++;
        ptr += which_len;
        index += which_len;
    }
    return found;
}

void libs_string_reverse(void *str)
{
    struct libs_string *s = libs_string_get(str);
    if (!s || s->len < 2 || s->enc == libs_str_type_invalid) return;

    size_t begin = 0, end = s->len -1;
    char *ptr = NULL, tmp;
    wchar_t *wptr = NULL, wtmp;

    if (s->enc == libs_utf8) {
        ptr = s->str;
        while (begin != end) {
            tmp = ptr[end];
            ptr[end] = ptr[begin];
            ptr[begin] = tmp;
            begin++;
            end--;
        }
    } else if (s->enc == libs_utf16){
        wptr = s->str;
        while (begin != end) {
            wtmp = wptr[end];
            wptr[end] = wptr[begin];
            wptr[begin] = wtmp;
            begin++;
            end--;
        }
    }
}

bool libs_string_cut(void *str, size_t begin, size_t length)
{
    struct libs_string *s = libs_string_get(str);
    bool result = false;
    if (s && s->len >= begin + length) {
        result = true;
        size_t offset, str_size;

        if (s->enc == libs_utf8) {
            offset = begin * sizeof (char);
            str_size = length * sizeof (char);
            ((char*) s->str)[length] = '\0';
        } else if (s->enc == libs_utf16) {
            offset = begin * sizeof (wchar_t);
            str_size = length * sizeof (wchar_t);
            ((char*) s->str)[length] = L'\0';
        }
        memmove(s->str, s->str + offset, str_size);
        s->str = realloc(s->str, str_size);
    }
    return result;
}
