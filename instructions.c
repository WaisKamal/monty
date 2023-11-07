#include <stdlib.h>
#include "instructions.h"
#include "stdio.h"
#include "utils.h"

/**
 * exec - executes the given instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec(stack_t** stack, unsigned int line_number) {
    instruction_t instructions[] = {
        { "push",  &exec_push  },
        { "pall",  &exec_pall  },
        { "pint",  &exec_pint  },
        { "pop",   &exec_pop   },
        { "swap",  &exec_swap  },
        { "add",   &exec_add   },
        { "sub",   &exec_sub   },
        { "div",   &exec_div   },
        { "mul",   &exec_mul   },
        { "mod",   &exec_mod   },
        { "pchar", &exec_pchar },
        { "pstr",  &exec_pstr  },
        { "rotl",  &exec_rotl  },
        { "rotr",  &exec_rotr  },
        { "stack", &exec_stack },
        { "queue", &exec_queue }
    };
    unsigned long int i;
    unsigned long instructions_count = sizeof(instructions) / sizeof(instruction_t);
    for (i = 0; i < instructions_count; i++) {
        if (!strcmp(state.args[0], instructions[i].opcode)) {
            instructions[i].f(stack, line_number);
            break;
        }
    }
}

/**
 * pop_top - removes the top element of the stack
 * 
 * @stack: pointer to the stack
*/
void pop_top(stack_t** stack) {
    /* Update the stack pointer */
    stack_t* current = *stack;
    *stack = (*stack)->prev;

    /* Set the next pointer of the new stack if it is not empty */
    if (*stack) {
        (*stack)->next = NULL;
    } else {
        state.stack_bottom = NULL;
    }

    /* Decrement stack size */
    state.stack_size--;

    /* Deallocate the popped element's memory */
    free(current);
}

/**
 * pop_bottom - removes the bottom element of the stack
 * 
 * @stack: pointer to the stack
*/
void pop_bottom(stack_t** stack) {
    /* Update the stack bottom pointer */
    stack_t* current = state.stack_bottom;
    state.stack_bottom = state.stack_bottom->next;

    /* Set the prev pointer of the stack bottom if stack is not empty */
    if (state.stack_bottom) {
        state.stack_bottom->prev = NULL;
    } else {
        *stack = NULL;
    }

    /* Decrement stack size */
    state.stack_size--;

    /* Deallocate the popped element's memory */
    free(current);
}

/**
 * exec_push - executes the push instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_push(stack_t** stack, unsigned int line_number) {
    stack_t* new_stack_entry = malloc(sizeof(stack_t));
    int operand;

    if (!new_stack_entry) {
        state.status = -1;
        fprintf(stderr, "Error: malloc failed\n");
        return;
    }

    if (state.arg_count < 2 || !is_valid_integer(state.args[1])) {
        state.status = -1;
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        return;
    } else {
        operand = atoi(state.args[1]);
    }

    new_stack_entry->n = operand;
    new_stack_entry->next = NULL;
    new_stack_entry->prev = *stack;
    
    if (*stack) {
        if (state.mode == STACK_MODE) {
            (*stack)->next = new_stack_entry;
            *stack = (*stack)->next;
        } else {
            new_stack_entry->next = state.stack_bottom;
            new_stack_entry->prev = NULL;
            state.stack_bottom->prev = new_stack_entry;
            state.stack_bottom = new_stack_entry;
        }
    } else {
        *stack = new_stack_entry;
        state.stack_bottom = *stack;
    }

    /* Increment stack size */
    state.stack_size++;
}

/**
 * exec_pall - executes the pall instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_pall(stack_t** stack, unsigned int line_number) {
    stack_t* current = *stack;
    while (current) {
        printf("%d\n", current->n);
        current = current->prev;
    }
}

/**
 * exec_pint - executes the pint instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_pint(stack_t** stack, unsigned int line_number) {
    if (!(*stack)) {
        state.status = -1;
        fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
        return;
    }
    printf("%d\n", (*stack)->n);
}

/**
 * exec_pop - executes the pop instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_pop(stack_t** stack, unsigned int line_number) {
    stack_t* current;
    if (!(*stack)) {
        state.status = -1;
        fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
        return;
    }

    if (state.mode == STACK_MODE) {
        pop_top(stack);
    } else {
        pop_bottom(stack);
    }
}

/**
 * exec_swap - executes the swap instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_swap(stack_t** stack, unsigned int line_number) {
    int* first;
    int* second;
    int temp;

    if (state.stack_size < 2) {
        state.status = -1;
        fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
        return;
    }

    first = &(*stack)->n;
    second = &(*stack)->prev->n;
    temp = *first;
    *first = *second;
    *second = temp;
}

/**
 * exec_add - executes the add instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_add(stack_t** stack, unsigned int line_number) {
    int* first;
    int* second;

    if (state.stack_size < 2) {
        state.status = -1;
        fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
        return;
    }

    /* Perform addition: second = second + first */
    first = &(*stack)->n;
    second = &(*stack)->prev->n;
    *second = (*second + *first);

    /* Remove the top element */
    pop_top(stack);
}

/**
 * exec_sub - executes the sub instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_sub(stack_t** stack, unsigned int line_number) {
    int* first;
    int* second;

    if (state.stack_size < 2) {
        state.status = -1;
        fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
        return;
    }

    /* Perform subtraction: second = second - first */
    first = &(*stack)->n;
    second = &(*stack)->prev->n;
    *second = (*second - *first);

    /* Remove the top element */
    pop_top(stack);
}

/**
 * exec_div - executes the div instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_div(stack_t** stack, unsigned int line_number) {
    int* first;
    int* second;

    if (state.stack_size < 2) {
        state.status = -1;
        fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
        return;
    }

    first = &(*stack)->n;
    second = &(*stack)->prev->n;

    if (*first == 0) {
        state.status = -1;
        fprintf(stderr, "L%d: division by zero\n", line_number);
        return;
    }

    /* Perform division: second = second / first */
    *second = (*second / *first);

    /* Remove the top element */
    pop_top(stack);
}

/**
 * exec_mul - executes the mul instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_mul(stack_t** stack, unsigned int line_number) {
    int* first;
    int* second;

    if (state.stack_size < 2) {
        state.status = -1;
        fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
        return;
    }

    /* Perform multiplication: second = second * first */
    first = &(*stack)->n;
    second = &(*stack)->prev->n;
    *second = (*second * *first);

    /* Remove the top element */
    pop_top(stack);
}

/**
 * exec_mod - executes the mod instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_mod(stack_t** stack, unsigned int line_number) {
    int* first;
    int* second;

    if (state.stack_size < 2) {
        state.status = -1;
        fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
        return;
    }

    first = &(*stack)->n;
    second = &(*stack)->prev->n;

    if (*first == 0) {
        state.status = -1;
        fprintf(stderr, "L%d: division by zero\n", line_number);
        return;
    }

    /* Perform modulus: second = second % first */
    *second = (*second % *first);

    /* Remove the top element */
    pop_top(stack);
}

/**
 * exec_pchar - executes the pchar instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_pchar(stack_t** stack, unsigned int line_number) {
    int first;

    if (!(*stack)) {
        state.status = -1;
        fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
        return;
    }

    first = (*stack)->n;

    if (!is_printable_ascii_char(first)) {
        state.status = -1;
        fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
        return;
    }

    printf("%c\n", (char)first);
}

/**
 * exec_pstr - executes the pstr instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_pstr(stack_t** stack, unsigned int line_number) {
    stack_t* stack_top = *stack;
    while (stack_top && stack_top->n && is_printable_ascii_char(stack_top->n)) {
        printf("%c", (char)stack_top->n);
        stack_top = stack_top->prev;
    }
    printf("\n");
}

/**
 * exec_rotl - executes the rotl instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_rotl(stack_t** stack, unsigned int line_number) {
    stack_t* second;
    /* rotl has no effect if stack size is less than 2 */
    if (state.stack_size > 1) {
        second = (*stack)->prev;
        second->next = NULL;

        (*stack)->next = state.stack_bottom;
        (*stack)->prev = NULL;
        state.stack_bottom->prev = *stack;
        state.stack_bottom = *stack;

        *stack = second;
    }
}

/**
 * exec_rotr - executes the rotr instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_rotr(stack_t** stack, unsigned int line_number) {
    stack_t* second_last;
    /* rotr has no effect if stack size is less than 2 */
    if (state.stack_size > 1) {
        second_last = state.stack_bottom->next;
        second_last->prev = NULL;

        (*stack)->next = state.stack_bottom;
        state.stack_bottom->next = NULL;
        state.stack_bottom->prev = *stack;
        *stack = state.stack_bottom;

        state.stack_bottom = second_last;
    }
}

/**
 * exec_stack - executes the stack instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_stack(stack_t** stack, unsigned int line_number) {
    state.mode = STACK_MODE;
}

/**
 * exec_queue - executes the queue instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_queue(stack_t** stack, unsigned int line_number) {
    state.mode = QUEUE_MODE;
}