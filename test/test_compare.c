#include <stdio.h>
#include "test.h"

#include <stringhelper/string.h>

int main(){
	string_t* abc = string_copy(&STRING_INITIALIZER, string_cstr("abc"));
	string_t* abc1 = string_copy(&STRING_INITIALIZER, string_cstr("abc1"));
	string_t* abc2 = string_copy(&STRING_INITIALIZER, string_cstr("abc2"));
	string_t* xyz = string_copy(&STRING_INITIALIZER, string_cstr("xyz"));
	
	ASSERT(string_compare(abc2, abc1)>0, "comp(abc2, abc1)>0");
	ASSERT(string_compare(abc1, abc2)<0, "comp(abc1, abc2)<0");
	ASSERT(string_compare(abc1, abc1)==0, "comp(abc1, abc1)==0");
	ASSERT(string_compare(abc1, abc)>0, "comp(abc1, abc)>0");
	ASSERT(string_compare(abc, abc1)<0, "comp(abc, abc1)<0");
	ASSERT(string_compare(abc, xyz)<0, "comp(abc, xyz)<0");
	ASSERT(string_compare(xyz, abc)>0, "comp(xyz, abc)>0");
	ASSERT(string_compare(abc1, xyz)<0, "comp(abc1, xyz)<0");
	ASSERT(string_compare(xyz, abc1)>0, "comp(xyz, abc1)>0");
	
	string_free(abc);
	string_free(abc1);
	string_free(abc2);
	string_free(xyz);
	
	return TEST_RESULT;
}
