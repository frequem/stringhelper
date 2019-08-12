#include <stringhelper/string.h>

#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

string_t string_cstr(char* cstr){
	string_t temp;
	temp.chars = cstr;
	temp.len = strlen(cstr);
	temp.maxlen = temp.len;
	return temp;
}

string_t string_char(char ch){
	static char c = '\0';
	c = ch;
	
	string_t temp;
	temp.chars = &c;
	temp.len = 1;
	temp.maxlen = temp.len;
	return temp;
}

string_t string_int(int i){
	static char buf[32];
	int l = snprintf(NULL, 0, "%i", i); // get string length
	snprintf(buf, l+1, "%i", i); // write i to str
	return string_cstr(buf);
}

string_t string_buf(char* buf, int size){
	string_t temp;
	temp.chars = buf;
	temp.len = size;
	temp.maxlen = size;
	return temp;
}

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

string_t* string_append(string_t* dest, string_t src, string_t in){
	return string_insert(dest, src, in, -1);
}

string_t* string_insert(string_t* dest, string_t src, string_t in, int at){
	int i = (at<0)?(at+1+src.len):at;
	i = (i<0)?0:((i>src.len)?src.len:i);
	int l = src.len + in.len;
	
	string_realloc(dest, l);
	memmove(dest->chars, src.chars, i); //move chars 0-i to start
	memmove(&(dest->chars[in.len+i]), &(src.chars[i]), src.len-i);//move chars i+1 - src.len to end
	memmove(&(dest->chars[i]), in.chars, in.len);//move in chars after i'th char
	dest->len = l;
	return dest;
}

string_t* string_clear(string_t* s){
	s->len = 0;
	return s;
}

string_t* string_toupper(string_t* dest, string_t src){
	string_realloc(dest, src.len);
	dest->len = src.len;
	
	for(int i=0; i<src.len; i++){
		dest->chars[i] = toupper((unsigned char) src.chars[i]);
	}
	
	return dest;
}

string_t* string_tolower(string_t* dest, string_t src){
	string_realloc(dest, src.len);
	dest->len = src.len;
	
	for(int i=0; i<src.len; i++){
		dest->chars[i] = tolower((unsigned char) src.chars[i]);
	}
	
	return dest;
}

string_t* string_substr(string_t* dest, string_t src, int start, int len){
	int i = (start<0)?(start+src.len):start;
	i = i<0?0:((i>=src.len)?(src.len):i);
	int l = (((i+len)>src.len)||len<0)?(src.len-i):len;
	
	string_realloc(dest, l);
	dest->len = l;
	memmove(dest->chars, &(src.chars[i]), l);
	
	return dest;
}

char string_charAt(string_t s, int at){
	char c;
	int i = (at<0)?(at+s.len):at;
	i = i<0?0:((i>=s.len)?(s.len-1):i);
		
	if(i >= 0 && i < s.len)
		c = s.chars[i];
	else
		c = '\0';
	return c;
}

unsigned int string_len(string_t s){
	return s.len;
}

unsigned int string_find(string_t s, string_t needle, int offset){
	unsigned int ls = string_len(s);
	unsigned int ln = string_len(needle);
	
	for(int i=offset; i<ls; i++){
		for(int j=0; i+j<ls; j++){
			if(ln <= j)
				break;
			if(string_charAt(s, i+j) == string_charAt(needle, j)){
				if(ln-1 == j)
					return i;
			}else{
				break;
			}
		}
	}
	return ls;
}

unsigned int string_find_reverse(string_t s, string_t needle, int offset){
	unsigned int ls = string_len(s);
	unsigned int ln = string_len(needle);
	
	for(int i=((offset>0)?offset:ls-1); i>=0; i--){
		for(int j=0; i-j>=0; j++){
			if(ln <= j)
				break;
			if(string_charAt(s, i-j) == string_charAt(needle, ln-j-1)){
				if(j == ln-1)
					return i-ln+1;
			}else{
				break;
			}
		}
	}
	return ls;
}

unsigned int string_replace(string_t* dest, string_t src, string_t find, string_t replace, int offset){
	unsigned int i = string_find(src, find, offset);
	
	if(i < string_len(src)){
		string_t copy = *string_copy(&STRING_INITIALIZER, src);
		
		string_substr(dest, src, 0, i);
		string_substr(&copy, copy, i+string_len(find), -1);
		
		string_append(dest, *dest, replace);
		string_append(dest, *dest, copy);
		
		string_free(&copy);
	}
	return i;
}

unsigned int string_replace_reverse(string_t* dest, string_t src, string_t find, string_t replace, int offset){
	unsigned int i = string_find_reverse(src, find, offset);
	
	if(i < string_len(src)){
		string_t copy = *string_copy(&STRING_INITIALIZER, src);
		
		string_substr(dest, src, 0, i);
		string_substr(&copy, copy, i+string_len(find), -1);
		
		string_append(dest, *dest, replace);
		string_append(dest, *dest, copy);
		
		string_free(&copy);
	}
	return i;
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

ssize_t string_write(int fd, string_t s){
	return write(fd, s.chars, s.len);
}
