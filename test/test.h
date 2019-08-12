#pragma once
#include <string.h>

int TEST_RESULT = 0;

void ASSERT(int cond, char* text){
	printf("Test: %s ", text);
	for(int i=strlen(text); i<100; i++){
		printf(".");
	}
	printf(" ");
	printf(cond?"\033[32mPassed":"\033[31mFailed");
	printf("\033[0m\n");
	
	if(!cond){
		TEST_RESULT = 1;
	}
}
