#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>

int main(){
	string_t s = *string_append(&STRING_INITIALIZER, string_cstr("test123test123test123"));
	
	ASSERT( 
		string_replace(&s, string_cstr("123"), string_cstr("456"), 0)==4 &&
		string_compare(s, string_cstr("test456test123test123")) == 0, 
		"replace(test123test123test123, 123)==test456test123test123"
	);
	
	ASSERT( 
		string_replace(&s, string_cstr("123"), string_cstr("456"), 0)==11 &&
		string_compare(s, string_cstr("test456test456test123")) == 0, 
		"replace(test456test123test123, 123)==test456test456test123"
	);
	
	ASSERT( 
		string_replace(&s, string_cstr("123"), string_cstr("456"), 0)==18 &&
		string_compare(s, string_cstr("test456test456test456")) == 0, 
		"replace(test456test456test123, 123)==test456test456test456"
	);
	
	ASSERT( 
		string_replace(&s, string_cstr("123"), string_cstr("456"), 0)==21 &&
		string_compare(s, string_cstr("test456test456test456")) == 0, 
		"replace(test456test456test456, 123)==test456test456test456"
	);
	
	ASSERT( 
		string_replace(&s, string_cstr("test456test456test456"), string_cstr(""), 0)==0 &&
		string_compare(s, string_cstr("")) == 0, 
		"replace(test456test456test456, )=="
	);
	
	ASSERT( 
		string_replace(&s, string_cstr(""), string_cstr("xyz"), 0)==0 &&
		string_compare(s, string_cstr("")) == 0, 
		"replace(, xyz)=="
	);
	
	string_free(&s);
	return TEST_RESULT;
}
