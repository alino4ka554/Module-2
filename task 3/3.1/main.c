#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

void printBits(mode_t st_mode) {
    for(int i = 4 * sizeof(st_mode); i >= 0; --i)
        printf("%d", ((st_mode >> i) & 1));
    getchar();
}

char* printLetters(mode_t st_mode) {
    static char str[10];  
    str[0] = (st_mode & S_IRUSR) ? 'r' : '-';
    str[1] = (st_mode & S_IWUSR) ? 'w' : '-';
    str[2] = (st_mode & S_IXUSR) ? 'x' : '-';
    str[3] = (st_mode & S_IRGRP) ? 'r' : '-';
    str[4] = (st_mode & S_IWGRP) ? 'w' : '-';
    str[5] = (st_mode & S_IXGRP) ? 'x' : '-';
    str[6] = (st_mode & S_IROTH) ? 'r' : '-';
    str[7] = (st_mode & S_IWOTH) ? 'w' : '-';
    str[8] = (st_mode & S_IXOTH) ? 'x' : '-';
    str[9] = '\0';
    return str;
}


mode_t printNumbers(char *str) {
    mode_t st_mode = 0;
    if (str[0] == 'r') st_mode |= S_IRUSR;
    if (str[1] == 'w') st_mode |= S_IWUSR;
    if (str[2] == 'x') st_mode |= S_IXUSR;
    if (str[3] == 'r') st_mode |= S_IRGRP;
    if (str[4] == 'w') st_mode |= S_IWGRP;
    if (str[5] == 'x') st_mode |= S_IXGRP;
    if (str[6] == 'r') st_mode |= S_IROTH;
    if (str[7] == 'w') st_mode |= S_IWOTH;
    if (str[8] == 'x') st_mode |= S_IXOTH;
    return st_mode;
}

mode_t modifyRights(mode_t st_mode, char *cmd) {
    mode_t new_mode = st_mode;
    int i = 0;
    if (cmd[0] != 'u' && cmd[0] != 'g' && cmd[0] != 'o' && cmd[0] != 'a') {
        printf("ERROR\n");
        return -1;
    }
    char delimiter, *who, *what;
    char delimiters[3] = { '-', '+', '=' };
    delimiter = (strchr(cmd, '+') != NULL) ? '+' : (strchr(cmd, '-') != NULL) ? '-' : '=';
    who = strtok(cmd, &delimiter);
    what = strtok(NULL, &delimiter);
    if(strchr(who, 'a'))
        who = "ugo";
    for(int j = 0; j < strlen(what); j++) {    
        for(int i = 0; i < strlen (who); i++) {
            mode_t bit = 0;
            switch(who[i]) {
                case 'u': 
                    bit = (what[j] == 'r') ? S_IRUSR : (what[j] == 'w') ? S_IWUSR : (what[j] == 'x') ? S_IXUSR : 0; 
                    break;
                case 'g': 
                    bit = (what[j] == 'r') ? S_IRGRP : (what[j] == 'w') ? S_IWGRP : (what[j] == 'x') ? S_IXGRP : 0; 
                    break;
                case 'o': 
                    bit = (what[j] == 'r') ? S_IROTH : (what[j] == 'w') ? S_IWOTH : (what[j] == 'x') ? S_IXOTH : 0; 
                    break;
                default:
                    return -1;
                    break;
            }
            if (bit != 0) {
                if (delimiter == '+') 
                    new_mode |= bit;
                else
                    new_mode &= ~bit;
            }
            else 
                return -1;
        } 
    }
    return new_mode;
}

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
                printf("Enter file name: \n");
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
                printf("%d", new_mode); printf("\n");
                if (new_mode != -1) {
                    printf("%s\n", printLetters(st.st_mode));
                    printf("%o\n", new_mode & 0777);
                    printf("%s\n", printLetters(new_mode));
                    printBits(new_mode);
                }
                else 
                    printf("ERROR\n");
                break;
            case 0:
                break;
        }
    } while (choice != 0);
}
