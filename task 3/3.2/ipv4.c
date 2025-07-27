#include "ipv4.h"

int* parseIP(const char *str) {
    static int ip_int[4];
    sscanf(str, "%d.%d.%d.%d", &ip_int[0], &ip_int[1], &ip_int[2], &ip_int[3]);
    return ip_int;
}

char* ipToString(int *ip) {
    static char ip_str[100];
    sprintf(ip_str, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
    return ip_str;
}