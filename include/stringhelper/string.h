#pragma once
#include <stdlib.h>

#define STRING_LEN_INCREMENT 32
#define STRING_INITIALIZER (string_t){NULL, 0, 0}

typedef struct{
	char* chars;
	unsigned int len;
	unsigned int maxlen;
} string_t;

/**
 * @brief Initializes an empty string
 * @param s the output string
 * @return s
 * @see string_free(string_t* s)
 */
string_t* string_init(string_t* s);
/**
 * @brief Frees a string previously initialized
 * @param s the string to be freed
 */
void string_free(string_t* s);

/**
 * @brief Copies a string
 * @param dest the output string
 * @param src the input string
 * @return dest
 */
string_t* string_copy(string_t* dest, string_t src);

/**
 * @brief Appends a string to another
 * @param dest the output string that src is appended to
 * @param src the string that is appended to dest
 * @return dest
 * @see string_append_cstr(string_t* dest, char* cstr)
 * @see string_append_char(string_t* dest, char ch)
 * @see string_append_int(string_t* dest, int i)
 */
string_t* string_append(string_t* dest, string_t src);
/**
 * @brief Appends a null-terminated string to a string
 * @param dest the output string that src is appended to
 * @param src the c string that is appended to dest
 * @return dest
 * @see string_append(string_t* dest, string_t src)
 * @see string_append_char(string_t* dest, char ch)
 * @see string_append_int(string_t* dest, int i)
 */
string_t* string_append_cstr(string_t* dest, char* cstr);
/**
 * @brief Appends a char to a string
 * @param dest the output string that ch is appended to
 * @param ch the character that is appended
 * @return dest
 * @see string_append(string_t* dest, string_t src)
 * @see string_append_cstr(string_t* dest, char* cstr)
 * @see string_append_int(string_t* dest, int i)
 */
string_t* string_append_char(string_t* dest, char ch);
/**
 * @brief Appends an int to a string_append
 * @param dest the output string that i as appended to
 * @param i the integer to be appended
 * @return dest
 * @see string_append(string_t* dest, string_t src)
 * @see string_append_cstr(string_t* dest, char* cstr)
 * @see string_append_char(string_t* dest, char ch)
 */
string_t* string_append_int(string_t* dest, int i);
/**
 * @brief Inserts a string into another
 * If at is non-negative, src is inserted at the at'th position of dest or at the back if at is too large
 * If at is negative, src is inserted at the at'th position from the back of dest or at the front if at is too small
 * @param dest the output string that src is inserted into
 * @param src the string that is inserted to dest
 * @param at the position where src is inserted
 * @return dest
 * @see string_insert_cstr(string_t* dest, char* cstr, int at)
 * @see string_insert_char(string_t* dest, char ch, int at)
 * @see string_insert_int(string_t* dest, int i, int at)
 */
string_t* string_insert(string_t* dest, string_t src, int at);
/**
 * @brief Inserts a null-terminated string into a string
 * If at is non-negative, src is inserted at the at'th position of dest or at the back if at is too large
 * If at is negative, src is inserted at the at'th position from the back of dest or at the front if at is too small
 * @param dest the output string that src is inserted into
 * @param src the c string that is inserted to dest
 * @param at the position where src is inserted
 * @return dest
 * @see string_insert(string_t* dest, string_t src, int at)
 * @see string_insert_char(string_t* dest, char ch, int at)
 * @see string_insert_int(string_t* dest, int i, int at)
 */
string_t* string_insert_cstr(string_t* dest, char* cstr, int at);
/**
 * @brief Inserts a char into a string
 * If at is non-negative, ch is inserted at the at'th position of dest or at the back if at is too large
 * If at is negative, ch is inserted at the at'th position from the back of dest or at the front if at is too small
 * @param dest the output string that ch is inserted into
 * @param ch the character that is inserted
 * @param at the position where ch is inserted
 * @return dest
 * @see string_insert(string_t* dest, string_t src, int at)
 * @see string_insert_cstr(string_t* dest, char* cstr, int)
 * @see string_insert_int(string_t* dest, int i, int at)
 */
string_t* string_insert_char(string_t* dest, char ch, int at);
/**
 * @brief Inserts an int into a string
 * If at is non-negative, i is inserted at the at'th position of dest or at the back if at is too large
 * If at is negative, i is inserted at the at'th position from the back of dest or at the front if at is too small
 * @param dest the output string that i is inserted into
 * @param i the int that is inserted
 * @param at the position where i is inserted
 * @return dest
 * @see string_insert(string_t* dest, string_t src, int at)
 * @see string_insert_cstr(string_t* dest, char* cstr, int)
 * @see string_insert_char(string_t* dest, char ch, int at)
 */
string_t* string_insert_int(string_t* dest, int i, int at);

/**
 * @brief Clears the string
 * @param s the string
 * @return s
 */
string_t* string_clear(string_t* s);

/**
 * @brief Converts a given string to upper case
 * @param s the string
 * @return s
 */
string_t* string_toupper(string_t* s);
/**
 * @brief Fetches a portion of the string
 * If start is non-negative, the output string will start at the start'th position of the original string.
 * If start is negative, the substring will start at the start'th position from the end of the original string.
 * If len is positive, the output string will contain at most len characters beginning from start (depending on the length of the input string).
 * If len is negative, the output string will contain all characters beginning from start.
 * @param s the string
 * @param start the start index of the new string
 * @param len the length of the new string
 * @return 0 on success, 1 otherwise
 */
int string_substr(string_t* s, int start, int len);

/**
 * @brief Fetches a char of the string at a given position
 * If at is positive, the output character is the at'th char of the original string
 * If at is negative, the output character is the at'th char from the end of the original string
 * @param s the input string
 * @param at the position of the desired character
 * @param ch the output character
 */
int string_charAt(string_t s, int at, char* ch);
/**
 * @brief Returns the string length of a given string
 * @param s the string
 * @return the string length
 */
unsigned int string_len(string_t s);
/**
 * @brief Compares two strings
 * @param s1 string to be compared
 * @param s2 string to be compared
 * @return <0 if the first char that doesn't match has a lower value in s1 than in s2, 0 if both strings are equal, >1 if the first character that does not match has a greater value in s1 than in s2
 */
int string_compare(string_t s1, string_t s2);

/**
 * @brief Compares a string with a null-terminated string
 * @param s1 string to be compared
 * @param s2 c string to be compared
 * @return <0 if the first char that doesn't match has a lower value in s1 than in s2, 0 if both strings are equal, >1 if the first character that does not match has a greater value in s1 than in s2
 */
int string_compare_cstr(string_t s1, char* cstr2);

/**
 * @brief Writes a string to a file descriptor
 * @param fd the file descriptor
 * @param s the string
 * @return the number of written bytes on success, -1 otherwise
 */
ssize_t string_write(int fd, string_t s);
