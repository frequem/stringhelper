#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>

int main(){
	string_t s = STRING_INITIALIZER;
	ASSERT(string_compare_cstr(s, "")==0, "Empty string");
	
	string_append_cstr(&s, "test123");
	ASSERT(string_compare_cstr(s, "test123")==0, "Append cstr");
	
	string_append_char(&s, 'x');
	ASSERT(string_compare_cstr(s, "test123x")==0, "Append char");
	
	string_append(&s, s);
	ASSERT(string_compare_cstr(s, "test123xtest123x")==0, "Append self");
	
	string_append_int(&s, 12345);
	ASSERT(string_compare_cstr(s, "test123xtest123x12345")==0, "Append int");
	
	string_free(&s);
	return TEST_RESULT;
}
