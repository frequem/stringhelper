#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>

int main(){
	
	string_t* s1 = string_copy(&STRING_INITIALIZER, string_int(123));
	string_t* s2 = string_copy(&STRING_INITIALIZER, string_int(456));
	
	ASSERT(string_compare(s1, s2)<0, "compare(123, 456)<0");
	ASSERT(string_compare(string_int(123), s2)<0, "compare(i123, 456)<0");
	ASSERT(string_compare(s1, string_int(456))<0, "compare(123, i456)<0");
	ASSERT(string_compare(string_int(123), string_int(456))<0, "compare(i123, i456)<0");
	
	string_copy(s1, string_char('a'));
	string_copy(s2, string_char('x'));
	
	ASSERT(string_compare(s1, s2)<0, "compare(a, x)<0");
	ASSERT(string_compare(string_char('a'), s2)<0, "compare(c(a), x)<0");
	ASSERT(string_compare(s1, string_char('x'))<0, "compare(a, c(x))<0");
	ASSERT(string_compare(string_char('a'), string_char('x'))<0, "compare(c(a), c(x))<0");
	
	
	string_copy(s1, string_float(123.456));
	string_copy(s2, string_float(654.321));
	
	ASSERT(string_compare(s1, s2)<0, "compare(123.456, 654.321)<0");
	ASSERT(string_compare(string_float(123.456), s2)<0, "compare(f123.456, 654.321)<0");
	ASSERT(string_compare(s1, string_float(654.321))<0, "compare(123.456, f654.321)<0");
	ASSERT(string_compare(string_float(123.456), string_float(654.321))<0, "compare(f123.456, f654.321)<0");
	
	ASSERT(
		string_replace(s1, string_char('a'), string_char('a'), string_char('x'), 0)==0 &&
		string_compare(s1, string_char('x'))==0,
		"replace(c(a), c(a), c(x))==c(x)"
	);
	
	ASSERT(
		string_replace(s1, string_int(1234), string_int(123), string_int(44), 0)==0 &&
		string_compare(s1, string_int(444))==0,
		"replace(i1234, i123, i44)==i444"
	);
	
	ASSERT(
		string_replace(s1, string_float(123.456), string_float(123.456), string_float(654.321), 0)==0 &&
		string_compare(s1, string_float(654.321))==0,
		"replace(f123.456, f123.456, f654.321)==f654.321"
	);
	
	
	
	string_free(s1);
	string_free(s2);
	
	return TEST_RESULT;
}
