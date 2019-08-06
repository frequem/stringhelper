#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>

int main(){
	string_t s = *string_append(&STRING_INITIALIZER, string_cstr("test123test123"));
	
	ASSERT(string_find(s, string_cstr("123"), 0)==4, "find(test123test123, 123)==4");
	ASSERT(string_find(s, string_int(123), 0)==4, "find(test123test123, (int)123)==4");
	ASSERT(string_find(s, string_int(23), 0)==5, "find(test123test123, (int)23)==5");
	ASSERT(string_find(s, string_cstr("t123"), 0)==3, "find(test123test123, t123)==3");
	ASSERT(string_find(s, string_cstr("test"), 0)==0, "find(test123test123, test)==0");
	
	ASSERT(string_find(s, string_cstr("t"), 0)==0, "find(test123test123, t)==0");
	ASSERT(string_find(s, string_cstr("t"), 1)==3, "find(test123test123, t, 1)==3");
	
	string_clear(&s);
	
	ASSERT(string_find(s, string_cstr(""), 0)==0, "find(\"\",\"\")==0");
	
	string_append(&s, string_cstr("xyzabcxyzabc"));
	ASSERT(string_find(s, string_cstr("xyab"), 0)==12, "find(xyzabcxyzabc,xyab)==12");
	
	ASSERT(string_find(s, string_cstr(""), 0)==12, "find(xyzabcxyzabc,\"\")==12");
	
	string_clear(&s);
	string_append(&s, string_cstr("test123test123"));
	
	ASSERT(string_find_reverse(s, string_cstr("123"), 0)==11, "find_reverse(test123test123, 123)==11");
	ASSERT(string_find_reverse(s, string_int(123), 0)==11, "find_reverse(test123test123, (int)123)==11");
	ASSERT(string_find_reverse(s, string_int(23), 0)==12, "find_reverse(test123test123, (int)23)==12");
	ASSERT(string_find_reverse(s, string_cstr("t123"), 0)==10, "find_reverse(test123test123, t123)==10");
	ASSERT(string_find_reverse(s, string_cstr("test"), 0)==7, "find_reverse(test123test123, test)==7");
	
	ASSERT(string_find_reverse(s, string_cstr("t"), 0)==10, "find_reverse(test123test123, t)==10");
	ASSERT(string_find_reverse(s, string_cstr("t"), 9)==7, "find_reverse(test123test123, t, 9)==7");
	
	string_clear(&s);
	
	ASSERT(string_find_reverse(s, string_cstr(""), 0)==0, "find_reverse(\"\",\"\")==0");
	
	string_append(&s, string_cstr("xyzabcxyzabc"));
	ASSERT(string_find_reverse(s, string_cstr("xyab"), 0)==12, "find_reverse(xyzabcxyzabc,xyab)==12");
	
	ASSERT(string_find_reverse(s, string_cstr(""), 0)==12, "find_reverse(xyzabcxyzabc,\"\")==12");

	string_free(&s);
	return TEST_RESULT;
}
