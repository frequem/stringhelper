#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>
#include <unistd.h>
int main(){
	string_t s = *string_copy(&STRING_INITIALIZER, string_cstr("abcdefghijklmnopqrstuvwxyz"));
	string_t res = STRING_INITIALIZER;
	
	string_erase(&res, s, 0, 7);
	ASSERT(string_compare(res, string_cstr("hijklmnopqrstuvwxyz"))==0, "erase(abcdefghijklmnopqrstuvwxyz, 0, 7)==hijklmnopqrstuvwxyz");	
	
	string_erase(&res, s, 0, 26);
	ASSERT(string_compare(res, string_cstr(""))==0, "erase(abcdefghijklmnopqrstuvwxyz, 0, 26)==");	
	
	string_erase(&res, s, -10, 7);
	ASSERT(string_compare(res, string_cstr("abcdefghijklmnopxyz"))==0, "erase(abcdefghijklmnopqrstuvwxyz, -10, 3)==abcdefghijklmnopxyz");	
	
	string_erase(&res, s, 3, 7);
	ASSERT(string_compare(res, string_cstr("abcklmnopqrstuvwxyz"))==0, "erase(abcdefghijklmnopqrstuvwxyz, 3, 3)==abcklmnopqrstuvwxyz");
	
	string_erase(&res, s, 26, 5);
	ASSERT(string_compare(res, string_cstr("abcdefghijklmnopqrstuvwxyz"))==0, "erase(abcdefghijklmnopqrstuvwxyz, 26, 5)==abcdefghijklmnopqrstuvwxyz");
	
	string_erase(&res, s, -32, 4);
	ASSERT(string_compare(res, string_cstr("efghijklmnopqrstuvwxyz"))==0, "erase(abcdefghijklmnopqrstuvwxyz, -32, 4)==efghijklmnopqrstuvwxyz");
	
	string_erase(&s, s, -26, 4);
	ASSERT(string_compare(s, string_cstr("efghijklmnopqrstuvwxyz"))==0, "erase(abcdefghijklmnopqrstuvwxyz, -26, 4)==efghijklmnopqrstuvwxyz (self)");

	string_free(&s);
	string_free(&res);
	return TEST_RESULT;
}
