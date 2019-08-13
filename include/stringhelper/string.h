#pragma once
#include <stdlib.h>

/** 
 * @brief The size the string grows by with each realloc.
 */
#define STRING_LEN_INCREMENT 32

/** 
 * @brief The string initializer that has to be used every time a string is created.
 */
#define STRING_INITIALIZER (string_t){malloc(0), 0, 0}

/**
 * @brief The buffer size of each conversion buffer needed for string_int, string_float and string_char.
 */
#define STRING_CONVERSION_BUFFER_SIZE 32

/**
 * @brief How many buffers there are for string_int, string_float and string_char conversions.
 * 3 buffers are needed for the string_replace function
 */
#define STRING_CONVERSION_BUFFERS 3

/**
 * The struct that represents a (stringhelper) string
 */
typedef struct{
	char* chars; /**< The memory location where the characters are stored */
	unsigned int len; /**< The current length of the string */
	unsigned int maxlen; /**< The maximum length of the string before it has to be reallocated */
} string_t;

/**
 * @brief Converts a char buffer into a string.
 * The resulting string will only contain correct data as long as buf lives
 * The resulting string must not be freed
 * This function should only be used as a parameter for another string_ function, never to initialize a variable
 * @param buf the char buffer to be converted
 * @param size the size of the char buffer
 */
string_t string_buf(char* buf, int size);

/**
 * @brief Converts a cstr into a string.
 * The resulting string will only contain correct data as long as cstr lives
 * The resulting string must not be freed
 * This function should only be used as a parameter for another string_ function, never to initialize a variable
 * @param cstr the null-terminated string to be converted
 */
string_t string_cstr(char* cstr);

/**
 * @brief Converts a char into a string.
 * The resulting string will only contain correct data until string_char will be called again
 * The resulting string must not be freed
 * This function should only be used as a parameter for another string_ function, never to initialize a variable
 * @param ch the char to be converted
 */
string_t string_char(char ch);

/**
 * @brief Converts a long long integer into a string.
 * The resulting string will only contain correct data until string_int will be called again
 * The resulting string should not be freed
 * This function should only be used as a parameter for another string_ function, never to initialize a variable
 * @param i the long long int to be converted
 */
string_t string_int(long long int i);

/**
 * @brief Converts a double into a string.
 * The resulting string will only contain correct data until string_float will be called again
 * The resulting string should not be freed
 * This function should only be used as a parameter for another string_ function, never to initialize a variable
 * @param f the double to be converted
 */
string_t string_float(double f);

/**
 * @brief Frees a string previously initialized.
 * @param s the string to be freed
 */
void string_free(string_t* s);

/**
 * @brief Copies a string.
 * @param dest the output string
 * @param src the input string
 * @return dest
 */
string_t* string_copy(string_t* dest, string_t src);

/**
 * @brief Appends a string to another.
 * @param dest the output string
 * @param src the input string that in is appended to
 * @param in the string that is appended to src
 * @return dest
 */
string_t* string_append(string_t* dest, string_t src, string_t in);

/**
 * @brief Inserts a string into another.
 * If at is non-negative, src is inserted at the at'th position of dest or at the back if at is too large
 * If at is negative, src is inserted at the at'th position from the back of dest or at the front if at is too small
 * @param dest the output string
 * @param src the input string that in is inserted into
 * @param in the string that in is inserted into src
 * @param at the position where src is inserted
 * @return dest
 */
string_t* string_insert(string_t* dest, string_t src, string_t in, int at);


/**
 * @brief Clears the string.
 * @param s the string
 * @return s
 */
string_t* string_clear(string_t* s);

/**
 * @brief Converts a given string to upper case.
 * @param dest the output string
 * @param src the input string
 * @return dest
 */
string_t* string_toupper(string_t* dest, string_t src);

/**
 * @brief Converts a given string to lower case.
 * @param dest the output string
 * @param src the input string
 * @return dest
 */
string_t* string_tolower(string_t* dest, string_t src);

/**
 * @brief Fetches a portion of the string.
 * If start is non-negative, the output string will start at the start'th position of the src string.
 * If start is negative, the substring will start at the start'th position from the end of the src string.
 * If len is positive, the output string will contain at most len characters beginning from start (depending on the length of the src string).
 * If len is negative, the output string will contain all characters beginning from start.
 * @param dest the output string
 * @param src the input string
 * @param start the start index of the new string
 * @param len the length of the new string
 * @return dest
 */
string_t* string_substr(string_t* dest, string_t src, int start, int len);

/**
 * @brief Erases part of the string.
 * If start is non-negative, the erased part of the string will start at the start'th position of the src string.
 * If start is negative, the erased part of the string will start at the start'th position from the end of the src string.
 * If len is positive, the erased part of the string will be at most len characters beginning from start (depending on the length of the src string) long.
 * If len is negative, the erased part of the string will contain all characters beginning from start.
 * @param dest the output string
 * @param src the input string
 * @param start the index of the first character to be erased
 * @param len the number of characters to erase
 * @return dest
 */
string_t* string_erase(string_t* dest, string_t src, int start, int len);

/**
 * @brief Fetches a char of the string at a given position.
 * If at is positive, the output character is the at'th char of the original string
 * If at is negative, the output character is the at'th char from the end of the original string
 * If the string is empty, this function always returns NULL
 * @param s the input string
 * @param at the position of the desired character
 * @return the character at the at'th position of the string or NULL
 */
char string_charAt(string_t s, int at);
/**
 * @brief Returns the string length of a given string.
 * @param s the string
 * @return the string length
 */
unsigned int string_len(string_t s);

/**
 * @brief Find the position of the first instance of a string inside another string.
 * @param s the string to search inside of
 * @param needle the string to find
 * @param offset the offset from which to search from
 * @return the index of needle inside s or the length of s if it was not found
 */
unsigned int string_find(string_t s, string_t needle, int offset);

/**
 * @brief Find the position of the last instance of a string inside another string.
 * If offset is 0 the string's length is used.
 * @param s the string to search inside of
 * @param needle the string to find
 * @param offset the offset from which to search from
 * @return the index of needle inside s or the length of s if it was not found
 */
unsigned int string_find_reverse(string_t s, string_t needle, int offset);

/**
 * @brief Replaces the first instance of replace inside of a s with find.
 * @param dest the output string
 * @param src the input string
 * @param find the string to be found
 * @param replace the string to replace find
 * @param offset the offset from which to replace from
 * @return the index of find inside the original src or the length of src if it was not found
 */
unsigned int string_replace(string_t* dest, string_t src, string_t find, string_t replace, int offset);

/**
 * @brief Replaces the last instance of replace inside of a s with find.
 * If offset is 0 the string's length is used.
 * @param dest the output string
 * @param src the input string
 * @param find the string to be found
 * @param replace the string to replace find
 * @param offset the offset from which to replace from
 * @return the index of find inside the original src or the length of src if it was not found
 */
unsigned int string_replace_reverse(string_t* dest, string_t src, string_t find, string_t replace, int offset);

/**
 * @brief Compares two strings.
 * @param s1 string to be compared
 * @param s2 string to be compared
 * @return <0 if the first char that doesn't match has a lower value in s1 than in s2, 0 if both strings are equal, >1 if the first character that does not match has a greater value in s1 than in s2
 * @see string_compare_cstr(string_t s1, char* cstr2)
 */
int string_compare(string_t s1, string_t s2);

/**
 * @brief Writes a string to a file descriptor.
 * @param fd the file descriptor
 * @param s the string
 * @return the number of written bytes on success, -1 otherwise
 */
ssize_t string_write(int fd, string_t s);
