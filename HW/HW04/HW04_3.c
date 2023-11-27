#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "stack.h"

//Prototype
void addLargeNumbers(const char *pNum1, const char *pNum2);

//Main program 
int main() {
    // Sample call
    addLargeNumbers("592", "3784"); // Expected output: 4376

    // Test cases for numbers larger than can be represented by a long
    addLargeNumbers("12345678901234567890", "98765432109876543210");// Expected output: 111111111111111111100
    addLargeNumbers("91827364581263485128364851", "91827364581263485128364851");
    addLargeNumbers("1234567890123456789001234567890", "9876543210987654321098706543210");

    return 0;
}
void addLargeNumbers(const char *pNum1, const char *pNum2) {
    Stack operandStack1, operandStack2, resultStack;
    void *data;
    int carry = 0, sum;

    stack_init(&operandStack1, free);
    stack_init(&operandStack2, free);
    stack_init(&resultStack, free);

    // Push numerals of the first and second numbers onto their respective stacks
    for (int i = 0; pNum1[i] != '\0'; i++) {
    int *val = (int *)malloc(sizeof(int));  // Added cast here
    *val = pNum1[i] - '0';
    stack_push(&operandStack1, val);
}
    for (int i = 0; pNum2[i] != '\0'; i++) {
    int *val = (int *)malloc(sizeof(int));  // Added cast here
    *val = pNum2[i] - '0';
    stack_push(&operandStack2, val);
}

    while (stack_size(&operandStack1) > 0 || stack_size(&operandStack2) > 0) {
        sum = carry;

        if (stack_size(&operandStack1) > 0) {
            stack_pop(&operandStack1, &data);
            sum += *(int *)data;
            free(data);
        }
        if (stack_size(&operandStack2) > 0) {
            stack_pop(&operandStack2, &data);
            sum += *(int *)data;
            free(data);
        }

        carry = sum / 10;
        int *resultVal = (int *)malloc(sizeof(int));
        *resultVal = sum % 10;
        stack_push(&resultStack, resultVal);
    }
    if (carry != 0) {
        int *resultVal = (int *)malloc(sizeof(int));
        *resultVal = carry;
        stack_push(&resultStack, resultVal);
    }

    // Pop and display the result
    while (stack_size(&resultStack) > 0) {
        stack_pop(&resultStack, &data);
        printf("%d", *(int *)data);
        free(data);
    }
    printf("\n");

    stack_destroy(&operandStack1);
    stack_destroy(&operandStack2);
    stack_destroy(&resultStack);
}