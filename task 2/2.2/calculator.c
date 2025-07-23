#include <stdio.h> 
#include "calculator.h"

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