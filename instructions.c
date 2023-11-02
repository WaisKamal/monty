#include <stdlib.h>
#include "instructions.h"
#include "stdio.h"

/**
 * exec - executes the given instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec(stack_t** stack, unsigned int line_number) {
    instruction_t instructions[] = {
        { "push", &exec_push },
        { "pall", &exec_pall },
        { "pint", &exec_pint },
        { "pop",  &exec_pop  },
        { "swap", &exec_swap },
        { "add",  &exec_add  },
        { "sub",  &exec_sub  },
        { "div",  &exec_div  },
        { "mul",  &exec_mul  },
        { "mod",  &exec_mod  }
    };
    unsigned long int i;
    unsigned long instructions_count = sizeof(instructions) / sizeof(instruction_t);
    for (i = 0; i < instructions_count; i++) {
        if (!strcmp(args[0], instructions[i].opcode)) {
            instructions[i].f(stack, line_number);
            break;
        }
    }
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
        status = -1;
        fprintf(stderr, "Error: malloc failed\n");
        return;
    }

    if (arg_count < 2 || !is_valid_integer(args[1])) {
        status = -1;
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        return;
    } else {
        operand = atoi(args[1]);
    }

    new_stack_entry->n = operand;
    new_stack_entry->next = NULL;
    new_stack_entry->prev = *stack;
    if (*stack) {
        (*stack)->next = new_stack_entry;
        (*stack) = (*stack)->next;
    } else {
        *stack = new_stack_entry;
    }

    /* Increment stack size */
    stack_size++;
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
        status = -1;
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
    if (!(*stack)) {
        status = -1;
        fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
        return;
    }

    /* Update the stack pointer */
    stack_t* current = *stack;
    *stack = (*stack)->prev;

    /* Set the next pointer of the new stack if it is not empty */
    if (*stack) {
        (*stack)->next = NULL;
    }

    /* Decrement stack size */
    stack_size--;

    /* Deallocate the popped element's memory */
    free(current);
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

    if (stack_size < 2) {
        status = -1;
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

    if (stack_size < 2) {
        status = -1;
        fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
        return;
    }

    /* Perform addition: second = second + first */
    first = &(*stack)->n;
    second = &(*stack)->prev->n;
    *second = (*second + *first);

    /* Remove the top element */
    exec_pop(stack, line_number);
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

    if (stack_size < 2) {
        status = -1;
        fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
        return;
    }

    /* Perform subtraction: second = second - first */
    first = &(*stack)->n;
    second = &(*stack)->prev->n;
    *second = (*second - *first);

    /* Remove the top element */
    exec_pop(stack, line_number);
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

    if (stack_size < 2) {
        status = -1;
        fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
        return;
    }

    first = &(*stack)->n;
    second = &(*stack)->prev->n;

    if (*first == 0) {
        status = -1;
        fprintf(stderr, "L%d: division by zero\n", line_number);
        return;
    }

    /* Perform division: second = second / first */
    *second = (*second / *first);

    /* Remove the top element */
    exec_pop(stack, line_number);
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

    if (stack_size < 2) {
        status = -1;
        fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
        return;
    }

    /* Perform subtraction: second = second - first */
    first = &(*stack)->n;
    second = &(*stack)->prev->n;
    *second = (*second * *first);

    /* Remove the top element */
    exec_pop(stack, line_number);
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

    if (stack_size < 2) {
        status = -1;
        fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
        return;
    }

    first = &(*stack)->n;
    second = &(*stack)->prev->n;

    if (*first == 0) {
        status = -1;
        fprintf(stderr, "L%d: division by zero\n", line_number);
        return;
    }

    /* Perform division: second = second / first */
    *second = (*second % *first);

    /* Remove the top element */
    exec_pop(stack, line_number);
}
