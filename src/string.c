#include <stringhelper/string.h>

#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>


static string_t string_conv_buf[STRING_CONVERSION_BUFFERS];
static char string_conv_buf_chars[STRING_CONVERSION_BUFFERS][STRING_CONVERSION_BUFFER_SIZE];
static int string_conv_buf_offset = 0;

static string_t* string_get_conv_buf(){
	string_t* conv = &string_conv_buf[string_conv_buf_offset];
	char* conv_buf = string_conv_buf_chars[string_conv_buf_offset];
	conv->chars = conv_buf;
	conv->len = 0;
	conv->maxlen = STRING_CONVERSION_BUFFER_SIZE;
	
	//increment for next conversion
	string_conv_buf_offset = (string_conv_buf_offset+1)%STRING_CONVERSION_BUFFERS;
	return conv;
}

string_t* string_buf(char* buf, int size){
	string_t* conv = string_get_conv_buf();
	conv->chars = buf;
	conv->len = size;
	conv->maxlen = size;
	return conv;
}

string_t* string_cstr(char* cstr){
	return string_buf(cstr, strlen(cstr));
}

string_t* string_char(char ch){
	string_t* conv = string_get_conv_buf();
	conv->chars[0] = ch;
	conv->len = 1;
	return conv;
}

string_t* string_int(long long int i){	
	string_t* conv = string_get_conv_buf();
	conv->len = snprintf(NULL, 0, "%lld", i); // get string length
	snprintf(conv->chars, conv->len+1, "%lld", i); // write i to str
	return conv;
}

string_t* string_float(double f){
	string_t* conv = string_get_conv_buf();
	conv->len = snprintf(NULL, 0, "%g", f); // get string length
	snprintf(conv->chars, conv->len+1, "%g", f); // write f to str
	return conv;
}

void string_free(string_t* s){
	free(s->chars);
}

static void string_realloc(string_t* s, int n){
	if(n <= s->maxlen){ return; }
	int new_len = STRING_LEN_INCREMENT;
	while(new_len < n){
		new_len += STRING_LEN_INCREMENT;
	}
	s->chars = realloc(s->chars, sizeof(char)*new_len);
	s->maxlen = new_len;
}

string_t* string_copy(string_t* dest, string_t* src){
	string_realloc(dest, src->len);
	memcpy(dest->chars, src->chars, src->len);
	dest->len = src->len;
	return dest;
}

string_t* string_append(string_t* dest, string_t* src, string_t* in){
	return string_insert(dest, src, in, -1);
}

string_t* string_insert(string_t* dest, string_t* src, string_t* in, int at){
	int i = (at<0)?(at+1+src->len):at;
	i = (i<0)?0:((i>src->len)?src->len:i);
	
	string_realloc(dest, src->len+in->len);
	memmove(dest->chars, src->chars, i); //move chars 0-i to start
	memmove(&(dest->chars[i+in->len]), &(src->chars[i]), src->len-i);//move chars i+1 - src->len to end
	memmove(&(dest->chars[i]), in->chars, in->len);//move in chars after i'th char
	dest->len = src->len+in->len;
	return dest;
}

string_t* string_clear(string_t* s){
	s->len = 0;
	return s;
}

string_t* string_toupper(string_t* dest, string_t* src){
	string_realloc(dest, src->len);
	dest->len = src->len;
	
	for(int i=0; i<src->len; i++){
		dest->chars[i] = toupper((unsigned char) src->chars[i]);
	}
	
	return dest;
}

string_t* string_tolower(string_t* dest, string_t* src){
	string_realloc(dest, src->len);
	dest->len = src->len;
	
	for(int i=0; i<src->len; i++){
		dest->chars[i] = tolower((unsigned char) src->chars[i]);
	}
	
	return dest;
}

string_t* string_substr(string_t* dest, string_t* src, int start, int len){
	int i = (start<0)?(start+src->len):start;
	i = i<0?0:((i>=src->len)?(src->len):i);
	int l = (((i+len)>src->len)||len<0)?(src->len-i):len;
	
	string_realloc(dest, l);
	dest->len = l;
	memmove(dest->chars, &(src->chars[i]), l);
	
	return dest;
}

string_t* string_erase(string_t* dest, string_t* src, int start, int len){
	int i = (start<0)?(start+src->len):start;
	i = i<0?0:((i>=src->len)?(src->len):i);
	int l = (((i+len)>src->len)||len<0)?(src->len-i):len;
	
	string_realloc(dest, src->len-l);
	memmove(dest->chars, src->chars, i);
	memmove(&dest->chars[i], &src->chars[i+l], src->len-i-l);
	dest->len = src->len-l;
	return dest;
}

char string_charAt(string_t* s, int at){
	char c;
	int i = (at<0)?(at+s->len):at;
	i = i<0?0:((i>=s->len)?(s->len-1):i);
		
	if(i >= 0 && i < s->len)
		c = s->chars[i];
	else
		c = '\0';
	return c;
}

unsigned int string_len(string_t* s){
	return s->len;
}

unsigned int string_find(string_t* s, string_t* needle, int offset){
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

unsigned int string_find_reverse(string_t* s, string_t* needle, int offset){
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

unsigned int string_replace(string_t* dest, string_t* src, string_t* find, string_t* replace, int offset){
	unsigned int i = string_find(src, find, offset);
	
	if(i < string_len(src)){
		string_t copy = *string_copy(&STRING_INITIALIZER, src);
		
		string_substr(dest, src, 0, i);
		string_substr(&copy, &copy, i+string_len(find), -1);
		
		string_append(dest, dest, replace);
		string_append(dest, dest, &copy);
		
		string_free(&copy);
	}
	return i;
}

unsigned int string_replace_reverse(string_t* dest, string_t* src, string_t* find, string_t* replace, int offset){
	unsigned int i = string_find_reverse(src, find, offset);
	
	if(i < string_len(src)){
		string_t copy = *string_copy(&STRING_INITIALIZER, src);
		
		string_substr(dest, src, 0, i);
		string_substr(&copy, &copy, i+string_len(find), -1);
		
		string_append(dest, dest, replace);
		string_append(dest, dest, &copy);
		
		string_free(&copy);
	}
	return i;
}

int string_compare(string_t* s1, string_t* s2){
	int min_len = (s1->len < s2->len)?s1->len:s2->len;
	int r = memcmp(s1->chars, s2->chars, min_len);
	
	if(r == 0){
		if(s1->len < s2->len){
			return -1;
		}else if(s2->len < s1->len){
			return 1;
		}
	}
	return r;
}

ssize_t string_write(int fd, string_t* s){
	return write(fd, s->chars, s->len);
}
