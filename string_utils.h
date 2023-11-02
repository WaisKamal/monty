#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdbool.h>

/**
 * get_word_count - counts the number of words in a string,
 * where a word is a contiguous substring of non-whitespace
 * characters
 * 
 * @str: the input string
 * 
 * Return - the number of words in the string
*/
int get_word_count(char* str);

/**
 * split_string - splits a string on whitespaces
 * 
 * @str: the string to split
 * 
 * Return - pointer to an array containing the split string
*/
char** split_string(char* str);

/**
 * substring - extracts a substring from the given string
 * 
 * @str: the original string
 * @from: the starting index of the substring
 * @to: the last index of the substring
 * 
 * Return - a newly allocated string str[from, to]
*/
char* substring(char* src, int from, int to);

/**
 * free_string_array - deallocates a dynamically-allocated
 * string array
 * 
 * @string_array: the string array to deallocate
*/
void free_string_array(char** string_array);

/**
 * is_valid_integer - checks if a string is covertible to integer
 * 
 * @str: the input string
 * 
 * Return - true if @str is convertible to integer, false otherwise
*/
bool is_valid_integer(char* str);

#endif