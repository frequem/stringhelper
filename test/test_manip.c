#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>

int main(){
	string_t s = *string_copy(&STRING_INITIALIZER, string_cstr("test123"));
	
	string_toupper(&s, s);
	ASSERT(string_compare(s, string_cstr("TEST123"))==0, "toupper");
	
	string_tolower(&s, s);
	ASSERT(string_compare(s, string_cstr("test123"))==0, "tolower");
	
	string_clear(&s);
	ASSERT(string_compare(s, string_cstr(""))==0, "clear");
	
	string_free(&s);
	return TEST_RESULT;
}
