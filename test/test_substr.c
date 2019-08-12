#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>
#include <unistd.h>
int main(){
	string_t s = *string_copy(&STRING_INITIALIZER, string_cstr("test123"));
	string_t sub = STRING_INITIALIZER;
	
	string_substr(&sub, s, 0, 4);
	ASSERT(string_compare(sub, string_cstr("test"))==0, "substr(test123, 0, 4)==test");	
	
	string_substr(&sub, s, 0, 7);
	ASSERT(string_compare(sub, string_cstr("test123"))==0, "substr(test123, 0, 7)==test");	
	
	string_substr(&sub, s, -3, 3);
	ASSERT(string_compare(sub, string_cstr("123"))==0, "substr(test123, -3, 3)==123");	
	
	string_substr(&sub, s, 3, 3);
	ASSERT(string_compare(sub, string_cstr("t12"))==0, "substr(test123, 3, 3)==t12");
	
	string_substr(&sub, s, 8, 5);
	ASSERT(string_compare(sub, string_cstr(""))==0, "substr(test123, 8, 5)==");
	
	string_substr(&sub, s, -8, 4);
	ASSERT(string_compare(sub, string_cstr("test"))==0, "substr(test123, -8, 4)==test");
	
	string_substr(&s, s, -8, 4);
	ASSERT(string_compare(s, string_cstr("test"))==0, "substr(test123, -8, 4)==test (self)");

	string_free(&s);
	string_free(&sub);
	return TEST_RESULT;
}
