#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>

int main(){
	string_t orig = *string_append_cstr(&STRING_INITIALIZER, "test123");
	string_t s = *string_copy(&STRING_INITIALIZER, orig);
	
	string_substr(&s, 0, 4);
	ASSERT(string_compare_cstr(s, "test")==0, "substr(test123, 0, 4)==test");	
	
	string_copy(&s, orig);
	string_substr(&s, 0, 7);
	ASSERT(string_compare_cstr(s, "test123")==0, "substr(test123, 0, 7)==test");	
	
	string_copy(&s, orig);
	string_substr(&s, -3, 3);
	ASSERT(string_compare_cstr(s, "123")==0, "substr(test123, -3, 3)==123");	
	
	string_copy(&s, orig);
	string_substr(&s, 3, 3);
	ASSERT(string_compare_cstr(s, "t12")==0, "substr(test123, 3, 3)==t12");
	
	string_copy(&s, orig);
	string_substr(&s, 8, 5);
	ASSERT(string_compare_cstr(s, "")==0, "substr(test123, 8, 5)==");
	
	string_copy(&s, orig);
	string_substr(&s, -8, 4);
	ASSERT(string_compare_cstr(s, "test")==0, "substr(test123, -8, 4)==test");

	string_free(&s);
	string_free(&orig);
	return TEST_RESULT;
}
