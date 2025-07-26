#include <stdio.h>

int* parseIP(char *str){
    char *ip[4];
    int ip_int[4];
    ip[0] = strtok(str, " ");
    for(int i = 0; i < 3; i++) {
        ip[i + 1] = strtok(NULL, " ");
    }
    for(int i = 0; i < 4; i++) {
        ip_int[i] = strtol(ip[i], NULL, 10);
    }
    return ip_int;
}

int main(int argc, char **argv) {
    if(argc != 4) {
        printf("Enter the gateway IP address, subnet mask and number of packets \n");
        return 1;
    }
    int count = 0;
    bool flag = false;
    int IP_Src[4], Mask[4], Net_Src[4], IP_Dst[4]; Net_Dst[4]; Result[4];
    IP_Src = parseIP(argv[2]);
    Mask = parseIP(argv[3]);
    int n_sockets = strtol(argv[4], NULL, 10);
    for(int i = 0; i < 4; i++) {
        Net_Src[i] = IP_Src[i] & Mask[i];
    }
    srand(time(NULL));
    while(n_sockets != 0) {
        for(int i = 0; i < 4; i++) {
            IP_Dst[i] = rand() % 256;
            Net_Dst[i] = IP_Dst[i] & Mask[i];
            Result[i] = Net_Dst[i] ^ Net_Src[i];
        }
        
    }
}