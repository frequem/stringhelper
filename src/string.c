#include <stringhelper/string.h>

#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

void string_free(string_t* s){
	free(s->chars);
}

static void string_realloc(string_t* s, int n){
	if(n <= s->maxlen){ return; }
	int new_len = STRING_LEN_INCREMENT;
	while(new_len <= n){ //if n is a multiple of INCREMENT, add an additional one
		new_len += STRING_LEN_INCREMENT;
	}
	s->chars = realloc(s->chars, sizeof(char)*new_len);
	s->maxlen = new_len;
}

string_t* string_copy(string_t* dest, string_t src){
	string_realloc(dest, src.len);
	memcpy(dest->chars, src.chars, src.len);
	dest->len = src.len;
	return dest;
}

string_t* string_append(string_t* dest, string_t src){
	string_realloc(dest, dest->len + src.len);
	memcpy(&(dest->chars[dest->len]), src.chars, src.len);
	dest->len += src.len;
	return dest;
}

string_t* string_append_cstr(string_t* dest, char* cstr){
	string_t temp;
	temp.chars = cstr;
	temp.len = strlen(cstr);
	temp.maxlen = temp.len;
	string_append(dest, temp);
	return dest;
}

string_t* string_append_char(string_t* dest, char ch){
	string_t temp;
	temp.chars = &ch;
	temp.len = 1;
	temp.maxlen = temp.len;
	string_append(dest, temp);
	return dest;
}

string_t* string_append_int(string_t* dest, int i){
	int l = snprintf(NULL, 0, "%i", i); // get string length
	char* str = malloc(sizeof(char)*(l+1));
	snprintf(str, l+1, "%i", i); // write i to str
	string_append_cstr(dest, str);
	free(str);
	return dest;
}

string_t* string_insert(string_t* dest, string_t src, int at){
	int i = (at<0)?(at+1+dest->len):at;
	i = (i<0)?0:((i>dest->len)?dest->len:i);
	int l = dest->len + src.len;
	string_realloc(dest, l);
	//chars 0-i are already at correct position
	memcpy(&(dest->chars[src.len+i]), &(dest->chars[i]), dest->len-i);//move chars i+1 - dest.len to end of string
	memcpy(&(dest->chars[i]), src.chars, src.len);//copy src chars after i'th char
	dest->len = l;
	return dest;
}

string_t* string_insert_cstr(string_t* dest, char* cstr, int at){
	string_t temp;
	temp.chars = cstr;
	temp.len = strlen(cstr);
	temp.maxlen = temp.len;
	string_insert(dest, temp, at);
	return dest;
}

string_t* string_insert_char(string_t* dest, char ch, int at){
	string_t temp;
	temp.chars = &ch;
	temp.len = 1;
	temp.maxlen = temp.len;
	string_insert(dest, temp, at);
	return dest;
}

string_t* string_insert_int(string_t* dest, int i, int at){
	int l = snprintf(NULL, 0, "%i", i); // get string length
	char* str = malloc(sizeof(char)*(l+1));
	snprintf(str, l+1, "%i", i); // write i to str
	string_insert_cstr(dest, str, at);
	free(str);
	return dest;
}

string_t* string_clear(string_t* s){
	s->len = 0;
	return s;
}

string_t* string_toupper(string_t* s){
	char* cstr = s->chars;
	for(int i=0; i<s->len; i++){
		*cstr = toupper((unsigned char) *cstr);
		cstr++;
	}
	return s;
}

string_t* string_tolower(string_t* s){
	char* cstr = s->chars;
	for(int i=0; i<s->len; i++){
		*cstr = tolower((unsigned char) *cstr);
		cstr++;
	}
	return s;
}

string_t* string_substr(string_t* s, int start, int len){
	int i = (start<0)?(start+s->len):start;
	i = i<0?0:((i>=s->len)?(s->len):i);
	
	int l = (((i+len)>s->len)||len<0)?(s->len-i):len;
	memmove(s->chars, &(s->chars[i]), l);
	s->len = l;
	return s;
}

char string_charAt(string_t s, int at, char* ch){
	char c;
	int i = (at<0)?(at+s.len):at;
	i = i<0?0:((i>=s.len)?(s.len-1):i);
	if(i >= 0 && i < s.len)
		c = s.chars[i];
	else
		c = '\0';
	
	if(ch != NULL){
		*ch = c;
	}
	return c;
}

unsigned int string_len(string_t s){
	return s.len;
}

int string_compare(string_t s1, string_t s2){
	int min_len = (s1.len < s2.len)?s1.len:s2.len;
	int r = memcmp(s1.chars, s2.chars, min_len);
	
	if(r == 0){
		if(s1.len < s2.len){
			return -1;
		}else if(s2.len < s1.len){
			return 1;
		}
	}
	return r;
}

int string_compare_cstr(string_t s1, char* cstr2){
	string_t temp;
	temp.chars = cstr2;
	temp.len = strlen(cstr2);
	temp.maxlen = temp.len;
	return string_compare(s1, temp);
}

ssize_t string_write(int fd, string_t s){
	return write(fd, s.chars, s.len);
}