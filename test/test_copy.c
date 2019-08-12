#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>

int main(){
	string_t s = *string_copy(&STRING_INITIALIZER, string_cstr("test123"));
	
	string_t s2 = STRING_INITIALIZER;
	string_copy(&s2, s);
	
	ASSERT(string_compare(s, s2)==0, "Compare copy to original");
	
	string_free(&s);
	string_free(&s2);
	
	
	return TEST_RESULT;
}
