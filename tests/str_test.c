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
#include <libsimple.h>
#include <assert.h>
#include <string.h>
#include <wchar.h>
#include "test.h"

void str_test(void)
{
    BEGIN_TEST("String");
    /* Value Creation */
    char **str = libs_string("this is a test string. this");
    assert(str);
    assert(strcmp("this is a test string. this", *str) == 0);

    /* Utility methods */
    int replace1 = libs_string_replace_char(str, 'g', 'd');
    int replace2 = libs_string_replace_cstr(str, "this", "test2");
    int replace3 = libs_string_replace_cstr(str, "test2", "this");
    int count1 = libs_string_count_char(str, 'i');
    int count2 = libs_string_count_cstr(str, "this");

    libs_string_reverse(str);
    libs_string_reverse(str);

    assert(libs_string_cut(str, 5, 2));
    assert(strcmp("is", *str) == 0);
    assert(replace1 && replace2 && replace3 && count1 == 4 && count2 == 2);

    libs_string_destroy(str);
    /* UTF8 */

    /* Value Creation */
    wchar_t **wstr = libs_wstring(L"안녕. 你好. ÜöäßABC");
    assert(wstr);
    assert(wcscmp(L"안녕. 你好. ÜöäßABC", *wstr) == 0);

    /* Utility methods */
    replace1 = libs_wstring_replace_char(wstr, L'안', L'?');
    replace2 = libs_wstring_replace_cstr(wstr, L"你好", L"Nihao");
    replace3 = libs_wstring_replace_cstr(wstr, L"Nihao", L"你好");
    libs_string_reverse(wstr);
    libs_string_reverse(wstr);
    assert(wcscmp(L"?녕. 你好. ÜöäßABC", *wstr) == 0);
    assert(replace1 && replace2 && replace3);

    libs_string_destroy(wstr);
}
