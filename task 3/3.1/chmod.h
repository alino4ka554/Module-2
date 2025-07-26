#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

void printBits(mode_t st_mode);
char* printLetters(mode_t st_mode);
mode_t printNumbers(char *str);
mode_t modifyRights(mode_t st_mode, char *cmd);