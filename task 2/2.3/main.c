#include <stdio.h> 
#include "calculator.h"

int main(void) {
    int choice; 
    float x, y;
    float (*operation)(float, float);
    do {
        for(int i = 0; i < COUNT; i++)
            printf("%d. %s", operations[i].number, operations[i].name);
        printf("0. Exit\n");
        printf("Select an action: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        if (choice >= 1 && choice <= COUNT) {
            printf("Enter the first number: ");
            scanf("%f", &x);
            printf("Enter the second number: ");
            scanf("%f", &y);
            operation = select(choice);
            printf("%f %c %f = %f\n", x, operations[choice - 1].action, y, operation(x, y));
        } 
        else if (choice == 0)
            break;
        else 
            printf("Wrong choice!\n"); 

    } while (choice != 5);
    return 0;
}