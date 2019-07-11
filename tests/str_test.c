#include <libsimple.h>
#include <assert.h>
#include <string.h>
#include <wchar.h>

void str_test(void)
{
	char **str = libs_string("test");
	assert(str);
	assert(strcmp("test", *str) == 0);
	libs_string_destroy(str);

	wchar_t **wstr = libs_wstring(L"안녕");
	assert(wstr);
	assert(wcscmp(L"안녕", *wstr) == 0);
	libs_string_destroy(wstr);
}
