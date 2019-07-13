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
static int offset = 0;

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

	if (offset == 0)
		offset = (int) &new_str->str - (int) new_str;

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

	if (offset == 0)
		offset = (int) &new_str->str - (int) new_str;
	return (wchar_t **) &new_str->str;
}

/* Internal utility */
struct libs_string *libs_string_get(void *str)
{
	assert(offset > 0);
	str -= offset;
	return (struct libs_string *) str;
}

const struct libs_string *libs_string_cget(const void *str)
{
	assert(offset > 0);
	str -= offset;
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
	s->len = strlen(s->str);
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

	while ((ptr = strstr(ptr, find))) {
		size_t ptr_len = strlen(ptr) + 1; /* Null terminator + 1 */
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

	while ((ptr = wcsstr(ptr, find))) {
		size_t ptr_len = wcslen(ptr) + 1; /* Null terminator + 1 */
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
