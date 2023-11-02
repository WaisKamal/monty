#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/**
 * remove_comments - Removes comments from a string by replacing the
 *                   first '#' with '\0'
 * 
 * @str: the input string
 * 
*/
void remove_comments(char* str);

/**
 * is_printable_ascii_char - Checks whether @ch is a printable ASCII
 *                           character
 * 
 * @ch: the input character's ASCII code
 * 
 * Return - true if @ch is a printable ASCII character, false
 *          otherwise
*/
bool is_printable_ascii_char(int ch);

#endif