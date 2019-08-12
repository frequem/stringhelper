#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>
#include <unistd.h>

int main(){
	string_t s = *string_copy(&STRING_INITIALIZER, string_cstr("123456789"));
	string_t abc = *string_copy(&STRING_INITIALIZER, string_cstr("abc"));
	
	string_t out = STRING_INITIALIZER;
	
	string_insert(&out, s, abc, 1);
	ASSERT(string_compare(out, string_cstr("1abc23456789"))==0, "Insert at positive inside");
	
	string_insert(&out, s, abc, -2);
	ASSERT(string_compare(out, string_cstr("12345678abc9"))==0, "Insert at negative inside");
	
	string_insert(&out, s, abc, 10);
	ASSERT(string_compare(out, string_cstr("123456789abc"))==0, "Insert at positive outside");
	
	string_insert(&out, s, abc, -11);
	ASSERT(string_compare(out, string_cstr("abc123456789"))==0, "Insert at negative outside");
	
	string_free(&out);
	
	string_insert(&s, s, abc, 2);
	ASSERT(string_compare(s, string_cstr("12abc3456789"))==0, "Insert at positive inside (self)");
	
	string_free(&abc);
	string_free(&s);
	return TEST_RESULT;
}
