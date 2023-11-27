/*
 * stack.h
 */
#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#include "list.h"

/*
 * Implement stacks as linked lists.
 */
typedef List Stack;

/*
 * Public Interface
 */

// Initialize the stack
void stack_init(Stack *stack, void (*destroy)(void *data));

// Destroy the stack
void stack_destroy(Stack *stack);

// Push an element onto the stack
int stack_push(Stack *stack, const void *data);

// Pop an element off the stack
int stack_pop(Stack *stack, void **data);

// Get the element at the top of the stack without removing it
void *stack_peek(Stack *stack);

// Get the current size of the stack
int stack_size(Stack *stack);

#endif
