#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>

int main(){
	string_t s = *string_append(&STRING_INITIALIZER, string_cstr("test123"));
	
	ASSERT(string_len(s)==7, "len(test123)==7");
	
	string_append(&s, string_cstr("abc"));
	ASSERT(string_len(s)==10, "len(test123abc)==10");
	
	string_clear(&s);
	ASSERT(string_len(s)==0, "len()==0");
	
	string_free(&s);
	
	s = STRING_INITIALIZER;
	ASSERT(string_len(s)==0, "len(init)==0");
	
	string_append(&s, string_cstr("test123"));
	
	ASSERT(string_charAt(s, 0)=='t', "charAt(test123, 0)=='t'");
	ASSERT(string_charAt(s, 1)=='e', "charAt(test123, 1)=='e'");
	ASSERT(string_charAt(s, -1)=='3', "charAt(test123, -1)=='3'");
	ASSERT(string_charAt(s, -2)=='2', "charAt(test123, -2)=='2'");
	
	ASSERT(string_charAt(s, 7)=='3', "charAt(test123, 7)=='3'");
	ASSERT(string_charAt(s, -8)=='t', "charAt(test123, -8)=='t'");
	
	string_clear(&s);
	
	ASSERT(string_charAt(s, 0)=='\0', "charAt(, 0)==NULL");
	ASSERT(string_charAt(s, -1)=='\0', "charAt(, -1)==NULL");
	ASSERT(string_charAt(s, -3)=='\0', "charAt(, -3)==NULL");
	ASSERT(string_charAt(s, 1)=='\0', "charAt(, 1)==NULL");
	ASSERT(string_charAt(s, 3)=='\0', "charAt(, 3)==NULL");
	
	string_free(&s);
	
	return TEST_RESULT;
}
