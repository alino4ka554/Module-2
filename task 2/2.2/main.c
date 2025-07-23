#include <stdio.h> 
#include "calculator.h"

int main(void) {
    int choice; 
    float x, y;
    do {
        printf("\n--- Calculator ---\n");
        printf("1. Addition (+) \n");
        printf("2. Substraction (-) \n");
        printf("3. Multiplication (*) \n");
        printf("4. Division (/) \n");
        printf("5. Exit\n");
        printf("Select an action: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        if (choice >= 1 && choice <= 4) {
            printf("Enter the first number: ");
            scanf("%f", &x);
            printf("Enter the second number: ");
            scanf("%f", &y);
        } 
        switch(choice) {
            case 1: printf("%d + %d = %d", x, y, additive(x, y)); break;
            case 2: printf("%d - %d = %d", x, y, subtract(x, y)); break;
            case 3: printf("%d * %d = %d", x, y, multiply(x, y)); break;
            case 4: printf("%d - %d = %f", x, y, division(x, y)); break;
            case 5: break;
            default: printf("Wrong choice!\n"); break;
        } 
    } while (choice != 5);
    return 0;
}