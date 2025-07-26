#include "chmod.h"

int main(void) {
    int choice;
    struct stat st;
    char input[100];
    do {
        printf("1. Enter rights (letters or numbers) and show bitmask\n");
        printf("2. Show file permissions\n");
        printf("3. Change access rights\n");
        printf("0. Exit\n");
        printf("Select an action: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch(choice) {
            case 1:
                printf("Enter permissions (for example: rwxr-xr-- or 754): ");
                fgets(input, 100, stdin);
                input[strcspn(input, "\n")] = 0;
                if(strlen(input) == 9) {
                    mode_t st_mode = printNumbers(input);
                    printf("%o\n", st_mode);
                    printBits(st_mode);
                }
                else {
                    int mode = strtol(input, NULL, 8);
                    printf("%s\n", printLetters(mode));
                    printBits(mode);
                }
                break;
            case 2:
                printf("Enter file name: ");
                fgets(input, 100, stdin);
                input[strcspn(input, "\n")] = 0;
                if(stat(input, &st) == -1) {
                    printf("ERROR\n");
                    break;
                }
                printf("%o\n", st.st_mode & 0777);
                printf("%s\n", printLetters(st.st_mode));
                printBits(st.st_mode);
                break;
            case 3:
                printf("chmod ");
                fgets(input, 100, stdin);
                input[strcspn(input, "\n")] = 0;
                char *what = strtok(input, " ");
                char *file = strtok(NULL, " ");
                if(stat(file, &st) == -1) {
                    printf("ERROR\n");
                    break;
                }
                mode_t new_mode = modifyRights(st.st_mode, what);
                if (new_mode != (mode_t)-1) {
                    printf("Old rights: %s\n", printLetters(st.st_mode));
                    printf("New rights: \n%o\n", new_mode & 0777);
                    printf("%s\n", printLetters(new_mode));
                    printBits(new_mode);
                }
                else 
                    printf("ERROR\n");
                break;
            case 0:
                break;
            default:
                break;
        }
    } while (choice != 0);
}
