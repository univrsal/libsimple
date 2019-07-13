#include <libsimple.h>
#include <assert.h>
#include <string.h>
#include <wchar.h>

void str_test(void)
{
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
	assert(strcmp("this is a test strind. this", *str) == 0);
	assert(replace1 && replace2 && replace3 && count1 == 4 && count2 == 2);

	libs_string_destroy(str);

	/* Value Creation */
	wchar_t **wstr = libs_wstring(L"안녕. 你好. ÜöäßABC");
	assert(wstr);
	assert(wcscmp(L"안녕. 你好. ÜöäßABC", *wstr) == 0);

	/* Utility methods */
	replace1 = libs_wstring_replace_char(wstr, L'안', L'?');
	replace2 = libs_wstring_replace_cstr(wstr, L"你好", L"Nihao");
	replace3 = libs_wstring_replace_cstr(wstr, L"Nihao", L"你好");

	assert(strcmp("안녕. 你好. ÜöäßABC", *wstr) == 0);
	assert(replace1 && replace2 && replace3);

	libs_string_destroy(wstr);
}
