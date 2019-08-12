#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>

int main(){
	string_t s = *string_copy(&STRING_INITIALIZER, string_cstr("test123test123test123"));
	
	ASSERT( 
		string_replace(&s, s, string_cstr("123"), string_cstr("456"), 0)==4 &&
		string_compare(s, string_cstr("test456test123test123")) == 0, 
		"replace(test123test123test123, 123)==test456test123test123"
	);
	
	ASSERT( 
		string_replace(&s, s, string_cstr("123"), string_cstr("456"), 0)==11 &&
		string_compare(s, string_cstr("test456test456test123")) == 0, 
		"replace(test456test123test123, 123)==test456test456test123"
	);
	
	ASSERT( 
		string_replace(&s, s, string_cstr("123"), string_cstr("456"), 0)==18 &&
		string_compare(s, string_cstr("test456test456test456")) == 0, 
		"replace(test456test456test123, 123)==test456test456test456"
	);
	
	ASSERT( 
		string_replace(&s, s, string_cstr("123"), string_cstr("456"), 0)==21 &&
		string_compare(s, string_cstr("test456test456test456")) == 0, 
		"replace(test456test456test456, 123)==test456test456test456"
	);
	
	ASSERT( 
		string_replace(&s, s, string_cstr("test456test456test456"), string_cstr(""), 0)==0 &&
		string_compare(s, string_cstr("")) == 0, 
		"replace(test456test456test456, )=="
	);
	
	ASSERT( 
		string_replace(&s, s, string_cstr(""), string_cstr("xyz"), 0)==0 &&
		string_compare(s, string_cstr("")) == 0, 
		"replace(, xyz)=="
	);
	
	string_clear(&s);
	string_append(&s, s, string_cstr("test123test123test123"));
	
	ASSERT( 
		string_replace_reverse(&s, s, string_cstr("123"), string_cstr("456"), 0)==18 &&
		string_compare(s, string_cstr("test123test123test456")) == 0, 
		"replace_rev(test123test123test123, 123)==test123test123test456"
	);
	
	ASSERT( 
		string_replace_reverse(&s, s, string_cstr("123"), string_cstr("456"), 0)==11 &&
		string_compare(s, string_cstr("test123test456test456")) == 0, 
		"replace_rev(test123test123test456, 123)==test123test456test456"
	);
	
	ASSERT( 
		string_replace_reverse(&s, s, string_cstr("123"), string_cstr("456"), 0)==4 &&
		string_compare(s, string_cstr("test456test456test456")) == 0, 
		"replace_rev(test123test456test456, 123)==test456test456test456"
	);
	
	ASSERT( 
		string_replace_reverse(&s, s, string_cstr("123"), string_cstr("456"), 0)==21 &&
		string_compare(s, string_cstr("test456test456test456")) == 0, 
		"replace_rev(test456test456test456, 123)==test456test456test456"
	);
	
	ASSERT( 
		string_replace_reverse(&s, s, string_cstr("test456test456test456"), string_cstr(""), 0)==0 &&
		string_compare(s, string_cstr("")) == 0, 
		"replace_rev(test456test456test456, )=="
	);
	
	ASSERT( 
		string_replace_reverse(&s, s, string_cstr(""), string_cstr("xyz"), 0)==0 &&
		string_compare(s, string_cstr("")) == 0, 
		"replace_rev(, xyz)=="
	);
	
	
	string_free(&s);
	return TEST_RESULT;
}
