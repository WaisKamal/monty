#include <stdio.h>
#include <stdlib.h>
#include "monty.h"
#include "instructions.h"
#include "utils.h"

state_t state;

int main(int argc, char** argv) {
    FILE* input_file;           /* The source file */
    char buffer[1024];          /* The buffer into which the source file will be read */
    int line_number = 1;        /* The current line number */
    int line_length;            /* The length of the current line */
    stack_t* stack_ptr = NULL;  /* Pointer to the stack */

    /* Initialize stack */
    state.stack_bottom = stack_ptr;
    state.stack_size = 0;
    state.mode = STACK_MODE;
    state.status = EXIT_SUCCESS;

    /* If no file is supplied */
    if (argc != 2) {
        fprintf(stderr, "USAGE: monty file\n");
        return EXIT_FAILURE;
    }

    /* Open source file */
    input_file = fopen(argv[1], "r");

    /* If file does not exist */
    if (input_file == NULL) {
        fprintf(stderr, "Can't open file %s", argv[1]);
        return EXIT_FAILURE;
    }

    /* Read first line */
    while (fgets(buffer, sizeof buffer, input_file)) {
        line_length = strlen(buffer);

        /* Skip empty lines */
        if (line_length == 0) {
            continue;
        }

        /* Remove any trailing newline character */
        if (buffer[line_length - 1] == '\n') {
            buffer[line_length - 1] = '\0';
            line_length--;
        }

        /* Trim line at the first '#' character */
        remove_comments(buffer);

        /* Parse line and extract arguments */
        state.args = split_string(buffer);
        state.arg_count = get_word_count(buffer);

        /* Ignore empty lines */
        if (state.arg_count > 0) {
            exec(&stack_ptr, line_number);
        }

        /* Exit if an error occurred */
        if (state.status == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }

        /* Increment current line number */
        line_number++;
    }

    return 0;
}