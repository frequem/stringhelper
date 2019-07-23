#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>

int main(){
	string_t s = *string_append_cstr(&STRING_INITIALIZER, "test123");
	
	string_toupper(&s);
	ASSERT(string_compare_cstr(s, "TEST123")==0, "toupper");
	
	string_tolower(&s);
	ASSERT(string_compare_cstr(s, "test123")==0, "tolower");
	
	string_clear(&s);
	ASSERT(string_compare_cstr(s, "")==0, "clear");
	
	return TEST_RESULT;
}
