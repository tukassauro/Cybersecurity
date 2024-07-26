#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IP_ADDRESS>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int meusocket;
    int conecta;
    int porta;
    int inicio = 1; // start from port 1, not 0
    int final = 65535;
    char *destino = argv[1];

    struct sockaddr_in alvo;
    alvo.sin_family = AF_INET;
    alvo.sin_addr.s_addr = inet_addr(destino);

    printf("Starting port scan on %s\n", destino);

    for (porta = inicio; porta <= final; porta++) {
        meusocket = socket(AF_INET, SOCK_STREAM, 0);
        if (meusocket < 0) {
            perror("Socket creation error");
            exit(EXIT_FAILURE);
        }

        alvo.sin_port = htons(porta);
        conecta = connect(meusocket, (struct sockaddr *)&alvo, sizeof(alvo));

        if (conecta == 0) {
            printf("Port %d - status [OPEN]\n", porta);
        } else {
            // Print closed port status for debugging
            printf("Port %d - status [CLOSED]\n", porta);
        }

        close(meusocket);
    }

    printf("Port scan completed.\n");

    return 0;
}
