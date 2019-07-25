#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>

int main(){
	string_t s_orig = *string_append(&STRING_INITIALIZER, string_cstr("123456789"));
	string_t s = STRING_INITIALIZER;
	
	string_t abc = *string_append(&STRING_INITIALIZER, string_cstr("abc"));
	string_copy(&s, s_orig);
	string_insert(&s, abc, 1);
	ASSERT(string_compare(s, string_cstr("1abc23456789"))==0, "Insert at positive inside");
	
	string_copy(&s, s_orig);
	string_insert(&s, abc, -2);
	ASSERT(string_compare(s, string_cstr("12345678abc9"))==0, "Insert at negative inside");
		
	string_copy(&s, s_orig);
	string_insert(&s, abc, 10);
	ASSERT(string_compare(s, string_cstr("123456789abc"))==0, "Insert at positive outside");
	
	string_copy(&s, s_orig);
	string_insert(&s, abc, -11);
	ASSERT(string_compare(s, string_cstr("abc123456789"))==0, "Insert at negative outside");
	string_free(&abc);
	
	string_free(&s);
	string_free(&s_orig);
	return TEST_RESULT;
}
