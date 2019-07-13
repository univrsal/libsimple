#ifndef LIB_SIMPLE_STRING_H
#define LIB_SIMPLE_STRING_H
#include "types.h"

/* The string creation methods return the direct pointer
 * to the char string, so it can be used with any standard
 * C method. This also means that it should only be
 * modified using libsimple methods
 */
struct libs_string;

struct libs_wstring;

enum libs_str_type
{
        libs_str_type_invalid = -1,
        libs_utf8,
        libs_utf16,
};

#if LIB_SIMPLEE_TYPEDEF
typedef struct libs_string libs_string_t;
#endif

/* Create a string with a string
 * copied over as the value
 */
extern DECLSPEC char **LIBS_CALL
libs_string(const char* str);

extern DECLSPEC wchar_t **LIBS_CALL
libs_wstring(const wchar_t* wstr);

/* Deletes a string created with libs_string
 * or libs_wstring. Do not pass a pointers
 * recieved from libs_string_get, instead
 * use the originally created pointer
 */
extern DECLSPEC void LIBS_CALL
libs_string_destroy(void *str);

/* Convert utf16 into utf8 */
extern DECLSPEC bool LIBS_CALL
libs_string_wcs_to_uf8(void *str);

/* Convert utf8 into utf16 */
extern DECLSPEC bool LIBS_CALL
libs_string_utf8_to_wcs(void *str);

/* Use this if the string was modified with
 * any external method to update the length value */
extern DECLSPEC void LIBS_CALL
libs_string_refresh(void *str);

/* === Util methods === */

/* Replace all occurences of one char with another
 * returns the amount of chars replaced
 * @str		simple string to modify
 * @find	character to find
 * @replace	character to replace with
 * @return	amount of characters replaced
 */
extern DECLSPEC int LIBS_CALL
libs_string_replace_char(void *str, char find, char replace);

extern DECLSPEC int LIBS_CALL
libs_wstring_replace_char(void *str, wchar_t find, wchar_t replace);

/* Replace all occurences of a string with another
 * returns the amount of strings replaced
 * @str		simple string to modify
 * @find	C string to find
 * @replace	C string to replace with
 * @return	amount of instances replaced
 */
extern DECLSPEC int LIBS_CALL
libs_string_replace_cstr(void *str, const char *find, const char *replace);

extern DECLSPEC int LIBS_CALL
libs_wstring_replace_cstr(void *str, const wchar_t *find, const wchar_t
                          *replace);

/* Count all occurences of a character in a string
 * @str		simple string to search
 * @find	the character to find
 * @return	the amount of instances found
 */
extern DECLSPEC int LIBS_CALL
libs_string_count_char(const void *str, char which);

extern DECLSPEC int LIBS_CALL
libs_wstring_count_char(const void *str, wchar_t which);

/* Count all occurences of a substring in a string
 * @str		simple string to search
 * @find	the C string to find
 * @return	the amount of instances found
 */
extern DECLSPEC int LIBS_CALL
libs_string_count_cstr(const void *str, const char *which);

extern DECLSPEC int LIBS_CALL
libs_wstring_count_cstr(const void *str, const wchar_t *which);

#endif /* Header guard */
