#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

void print(int num) {
    printf("%d\n", num);
}



void die_error(char* msg) {
    puts("EXIT:");
    puts(msg);
    exit(-1);
}

int main() {

    int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(101);
    address.sin_addr.s_addr = inet_addr("10.0.0.18");

    int status = connect(sock, (struct sockaddr*) &address, 8);





    return 0;
}