#include <stdio.h> 
#include "calculator.h"

Operation operations[COUNT] = {
    {1, "Addition (+) \n", '+'}, 
    {2, "Substraction (-) \n", '-'},
    {3, "Multiplication (*) \n", '*'},
    {4, "Division (/) \n", '/'}
};

float additive(float x, float y) {
    return x + y;
}

float subtract(float x, float y) {
    return x - y;
}

float multiply(float x, float y) {
    return x * y;
}

float division(float x, float y) {
    if (y == 0) {
        printf("Division by zero!\n");
        return 0;
    }
    return (float)x / y;
}

float (*select(int choice)) (float, float) {
    switch (choice) {
        case 1: return additive;
        case 2: return subtract;
        case 3: return multiply;
        case 4: return division;
    }
}