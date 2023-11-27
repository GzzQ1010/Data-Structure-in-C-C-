/*
 * stack.c
 */
#include <stdlib.h>

#include "list.h"
#include "stack.h"

// Initialize the stack
void stack_init(Stack *stack, void (*destroy)(void *data)) {
    list_init(stack, destroy);
}

// Destroy the stack
void stack_destroy(Stack *stack) {
    list_destroy(stack);
}

// Push data onto the stack
int stack_push(Stack *stack, const void *data) {
    // Insert the data at the beginning of the list
    return list_ins_next(stack, NULL, data);
}

// Pop data off the stack
int stack_pop(Stack *stack, void **data) {
    // Remove the first element from the list
    return list_rem_next(stack, NULL, data);
}

// Peek at the top of the stack
void *stack_peek(Stack *stack) {
    // Return the data at the beginning of the list if it's not empty
    return (stack->head == NULL ? NULL : stack->head->data);
}

// Return the size of the stack
int stack_size(Stack *stack) {
    return list_size(stack);
}

