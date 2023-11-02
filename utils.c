#include <string.h>
#include "utils.h"

/**
 * remove_comments - Removes comments from a string by
 *                   replacing the first '#' with '\0'
 * 
 * @str: the input string
 * 
*/
void remove_comments(char* str) {
    int str_length = strlen(str);
    int i;
    for (i = 0; i < str_length; i++) {
        if (str[i] == '#') {
            str[i] = '\0';
            break;
        }
    }
}

/**
 * is_printable_ascii_char - Checks whether @ch is a printable ASCII
 *                           character
 * 
 * @ch: the input character's ASCII code
 * 
 * Return - true if @ch is a printable ASCII character, false
 *          otherwise
*/
bool is_printable_ascii_char(int ch) {
    return (ch >= 32 && ch <= 127);
}