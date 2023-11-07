#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_h

#include "monty.h"

#define STACK_MODE 0
#define QUEUE_MODE 1

typedef struct state_s {
    stack_t* stack_bottom;  /* Pointer to the bottom of the stack */
    int stack_size;         /* The size of the stack */
    char** args;            /* The opcode and its arguments */
    int arg_count;          /* The number of arguments */
    int mode;               /* The operating mode - 0: stack, 1: queue */
    int status;             /* The status code for the last instruction -
                            * 0: sucess, -1: failure */
} state_t;

extern state_t state;

/**
 * exec - executes the given instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec(stack_t** stack, unsigned int line_number);

/**
 * pop_top - removes the top element of the stack
 * 
 * @stack: pointer to the stack
*/
void pop_top(stack_t** stack);

/**
 * pop_bottom - removes the bottom element of the stack
 * 
 * @stack: pointer to the stack
*/
void pop_bottom(stack_t** stack);

/**
 * exec_push - executes the push instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_push(stack_t** stack, unsigned int line_number);

/**
 * exec_pall - executes the pall instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_pall(stack_t** stack, unsigned int line_number);

/**
 * exec_pint - executes the pint instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_pint(stack_t** stack, unsigned int line_number);

/**
 * exec_pop - executes the pop instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_pop(stack_t** stack, unsigned int line_number);

/**
 * exec_swap - executes the swap instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_swap(stack_t** stack, unsigned int line_number);

/**
 * exec_add - executes the add instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_add(stack_t** stack, unsigned int line_number);

/**
 * exec_sub - executes the sub instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_sub(stack_t** stack, unsigned int line_number);

/**
 * exec_div - executes the div instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_div(stack_t** stack, unsigned int line_number);

/**
 * exec_mul - executes the mul instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_mul(stack_t** stack, unsigned int line_number);

/**
 * exec_mod - executes the mod instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_mod(stack_t** stack, unsigned int line_number);

/**
 * exec_pchar - executes the pchar instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_pchar(stack_t** stack, unsigned int line_number);

/**
 * exec_pstr - executes the pstr instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_pstr(stack_t** stack, unsigned int line_number);

/**
 * exec_rotl - executes the rotl instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_rotl(stack_t** stack, unsigned int line_number);

/**
 * exec_rotr - executes the rotr instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_rotr(stack_t** stack, unsigned int line_number);

/**
 * exec_stack - executes the stack instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_stack(stack_t** stack, unsigned int line_number);

/**
 * exec_queue - executes the queue instruction
 * 
 * @stack: pointer to the stack
 * @line_number: the line number of the instruction
 * 
*/
void exec_queue(stack_t** stack, unsigned int line_number);

#endif
