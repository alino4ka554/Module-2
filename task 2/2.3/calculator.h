#define MAX_LENGTH 50
#define COUNT 4

typedef struct Operation {
    int number;
    char name[MAX_LENGTH];
    char action;
} Operation;

extern Operation operations[COUNT];

float additive(float x, float y);
float subtract(float x, float y);
float multiply(float x, float y);
float division(float x, float y);
float (*select(int choice)) (float, float);
