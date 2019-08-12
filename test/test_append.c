#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>
#include <unistd.h>

int main(){
	string_t s = STRING_INITIALIZER;
	ASSERT(string_compare(s, string_cstr(""))==0, "Empty string");
	
	string_append(&s, s, string_cstr("test123"));
	ASSERT(string_compare(s, string_cstr("test123"))==0, "Append cstr");
	
	string_append(&s, s, string_char('x'));
	ASSERT(string_compare(s, string_cstr("test123x"))==0, "Append char");
	
	string_append(&s, s, s);
	ASSERT(string_compare(s, string_cstr("test123xtest123x"))==0, "Append self");
	
	string_append(&s, s, string_int(12345));
	ASSERT(string_compare(s, string_cstr("test123xtest123x12345"))==0, "Append int");
	
	char buf[3] = {'a', 'b', 'c'};
	string_append(&s, s, string_buf(buf, sizeof(buf)));
	ASSERT(string_compare(s, string_cstr("test123xtest123x12345abc"))==0, "Append char buf");
	
	string_free(&s);
	return TEST_RESULT;
}
