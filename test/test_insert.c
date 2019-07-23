#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>

int main(){
	string_t s_orig = *string_append_cstr(&STRING_INITIALIZER, "123456789");
	string_t s = STRING_INITIALIZER;
	
	//stringhelper string
	string_t abc = *string_append_cstr(&STRING_INITIALIZER, "abc");
	string_copy(&s, s_orig);
	string_insert(&s, abc, 1);
	ASSERT(string_compare_cstr(s, "1abc23456789")==0, "Insert at positive inside");
	
	string_copy(&s, s_orig);
	string_insert(&s, abc, -2);
	ASSERT(string_compare_cstr(s, "12345678abc9")==0, "Insert at negative inside");
		
	string_copy(&s, s_orig);
	string_insert(&s, abc, 10);
	ASSERT(string_compare_cstr(s, "123456789abc")==0, "Insert at positive outside");
	
	string_copy(&s, s_orig);
	string_insert(&s, abc, -11);
	ASSERT(string_compare_cstr(s, "abc123456789")==0, "Insert at negative outside");
	string_free(&abc);
	
	//cstr
	string_copy(&s, s_orig);
	string_insert_cstr(&s, "abc", 1);
	ASSERT(string_compare_cstr(s, "1abc23456789")==0, "Insert cstr at positive inside");
	
	string_copy(&s, s_orig);
	string_insert_cstr(&s, "abc", -2);
	ASSERT(string_compare_cstr(s, "12345678abc9")==0, "Insert cstr at negative inside");
		
	string_copy(&s, s_orig);
	string_insert_cstr(&s, "abc", 10);
	ASSERT(string_compare_cstr(s, "123456789abc")==0, "Insert cstr at positive outside");
	
	string_copy(&s, s_orig);
	string_insert_cstr(&s, "abc", -11);
	ASSERT(string_compare_cstr(s, "abc123456789")==0, "Insert cstr at negative outside");
	
	//char
	
	string_copy(&s, s_orig);
	string_insert_char(&s, 'a', 1);
	ASSERT(string_compare_cstr(s, "1a23456789")==0, "Insert char at positive inside");
	
	string_copy(&s, s_orig);
	string_insert_char(&s, 'a', -2);
	ASSERT(string_compare_cstr(s, "12345678a9")==0, "Insert char at negative inside");
		
	string_copy(&s, s_orig);
	string_insert_char(&s, 'a', 10);
	ASSERT(string_compare_cstr(s, "123456789a")==0, "Insert char at positive outside");
	
	string_copy(&s, s_orig);
	string_insert_char(&s, 'a', -11);
	ASSERT(string_compare_cstr(s, "a123456789")==0, "Insert char at negative outside");
	
	//int
	
	string_copy(&s, s_orig);
	string_insert_int(&s, 1001, 1);
	ASSERT(string_compare_cstr(s, "1100123456789")==0, "Insert int at positive inside");
	
	string_copy(&s, s_orig);
	string_insert_int(&s, 1001, -2);
	ASSERT(string_compare_cstr(s, "1234567810019")==0, "Insert int at negative inside");
		
	string_copy(&s, s_orig);
	string_insert_int(&s, 1001, 10);
	ASSERT(string_compare_cstr(s, "1234567891001")==0, "Insert int at positive outside");
	
	string_copy(&s, s_orig);
	string_insert_int(&s, 1001, -11);
	ASSERT(string_compare_cstr(s, "1001123456789")==0, "Insert int at negative outside");
	
	string_free(&s);
	string_free(&s_orig);
	return TEST_RESULT;
}
