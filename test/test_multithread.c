#include <stdio.h>
#include <threads.h>
#include "test.h"

#include <stringhelper/string.h>
#include <unistd.h>


int f1(void *arg){
	string_t a = *string_char('A');
	thrd_sleep(&(struct timespec){0, 2e6}, NULL);
	return string_compare(&a, string_char('A'))!=0;
}

int f2(void *arg){
	string_t b;
	
	for(int i=0; i<STRING_CONVERSION_BUFFERS; i++){
		b = *string_char('B');
	}
	
	return 0;
}

int f3(void *arg){
	return string_compare((string_t*)arg, string_char('C'))!=0;
}

int main(){
	thrd_t t1, t2, t3;
	int r1, r3;
	
	thrd_create(&t1, f1, NULL);
	thrd_create(&t2, f2, NULL);
	thrd_create(&t3, f3, string_char('C'));
	
	thrd_join(t1, &r1);
	thrd_join(t2, NULL);
	thrd_join(t3, &r3);
	
	ASSERT(r1==0, "f1 correct");
	ASSERT(r3==0, "f3 correct");
	
	return TEST_RESULT;
}
