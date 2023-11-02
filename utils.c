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
    for (int i = 0; i < str_length; i++) {
        if (str[i] == '#') {
            str[i] = '\0';
            break;
        }
    }
}