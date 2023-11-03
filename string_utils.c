#include <stdlib.h>
#include <string.h>
#include "string_utils.h"

/**
 * substring - extracts a substring from the given string
 * 
 * @str: the original string
 * @from: the starting index of the substring
 * @to: the last index of the substring
 * 
 * Return - a newly allocated string str[from, to]
*/
char* substring(char* src, int from, int to) {
    char* result = malloc((to - from + 2) * sizeof(char));
    int i;
    for (i = from; i <= to; i++) {
        result[i - from] = src[i];
    }
    result[to - from + 1] = '\0';
    return result;
}

/**
 * get_word_count - counts the number of words in a string,
 * where a word is a contiguous substring of non-whitespace
 * characters
 * 
 * @str: the input string
 * 
 * Return - the number of words in the string
*/
int get_word_count(char* str) {
    int length = strlen(str);
    int word_count;
    int i;
    if (length == 0) {
        return 0;
    }
    word_count = (str[0] != ' ');
    for (i = 1; i < length; i++) {
        word_count += (str[i - 1] == ' ' && str[i] != ' ');
    }
    return word_count;
}

/**
 * split_string - splits a string on whitespaces
 * 
 * @str: the string to split
 * 
 * Return - pointer to an array containing the split string
*/
char** split_string(char* str) {
    int length = strlen(str);
    int word_start = -1;
    int res_idx = 0;
    int word_count = get_word_count(str);
    int i;
    char** result;

    result = malloc((word_count + 1) * sizeof(char));
    for (i = 0; i < length; i++) {
        if (str[i] == ' ') {
            if (word_start != -1) {
                result[res_idx++] = substring(str, word_start, i - 1);
                word_start = -1;
            }
        } else {
            if (word_start == -1) {
                word_start = i;
            }
        }
    }
    if (word_start != -1) {
        result[res_idx++] = substring(str, word_start, i - 1);
    }
    result[res_idx] = NULL;
    return result;
}

/**
 * free_string_array - deallocates a dynamically-allocated
 * string array
 * 
 * @string_array: the string array to deallocate
*/
void free_string_array(char** string_array) {
    char* start = *string_array;
    while (start) {
        free(start);
        start++;
    }
    free(string_array);
}

/**
 * is_valid_integer - checks if a string is covertible to integer
 * 
 * @str: the input string
 * 
 * Return - true if @str is convertible to integer, false otherwise
*/
bool is_valid_integer(char* str) {
    while (*str) {
        if (*str < '0' || *str > '9') {
            return false;
        }
        str++;
    }
    return true;
}
