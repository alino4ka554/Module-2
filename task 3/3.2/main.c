#include "ipv4.h"

int main(int argc, char **argv) {
    if(argc != 4) {
        printf("Enter the gateway IP address, subnet mask and number of packets \n");
        return 1;
    }
    int count = 0;
    int IP_Src[4], Mask[4], Net_Src[4], IP_Dst[4], Net_Dst[4], Result[4];
    int *tmp;
    tmp = parseIP(argv[1]);
    for (int i = 0; i < 4; i++) IP_Src[i] = tmp[i];
    tmp = parseIP(argv[2]);
    for (int i = 0; i < 4; i++) Mask[i] = tmp[i];
    int n_sockets = strtol(argv[3], NULL, 10);
    int total = n_sockets;
    for(int i = 0; i < 4; i++) {
        Net_Src[i] = IP_Src[i] & Mask[i];
    }
    srand(time(NULL));
    while(n_sockets != 0) {
        bool flag = true;
        for(int i = 0; i < 4; i++) {
            IP_Dst[i] = rand() % 256;
            Net_Dst[i] = IP_Dst[i] & Mask[i];
            Result[i] = Net_Dst[i] ^ Net_Src[i];
            if(Result[i] != 0) 
                flag = false;
        }
        printf("IP %s ", ipToString(IP_Dst));
        if(flag) {
            printf("belongs to the subnet %s\n", argv[1]);
            count++;
        }
        else 
            printf("doesn't belongs to the subnet %s\n", argv[1]);
        n_sockets--;
    }
    printf("---Statistics---\n");
    printf("%d packets were intended for nodes of this subnet (%.2f%%)\n", count, count * 100.0 / total);
    printf("%d packets were intended for nodes of other networks (%.2f%%)", total - count, ((total - count) * 100.0) / total);
}