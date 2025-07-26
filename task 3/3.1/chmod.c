#include "chmod.h"

void printBits(mode_t st_mode) {
    for(int i = 4 * sizeof(st_mode); i >= 0; --i)
        printf("%d", ((st_mode >> i) & 1));
    printf("\n");
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
                    return (mode_t)-1;
            }
            if (bit != 0) {
                if (delimiter == '+') 
                    new_mode |= bit;
                else if (delimiter == '-')
                    new_mode &= ~bit;
                else if (delimiter == '=')
                    new_mode = (new_mode & ~bit) | bit;
            }
            else 
                return (mode_t)-1;
        } 
    }
    return new_mode;
}