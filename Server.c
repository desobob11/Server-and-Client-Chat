#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>

void print(int num) {
    printf("%d\n", num);
}



void die_error() {
    puts("EXIT:");
    puts(strerror(errno));
    exit(-1);
}

time_t t;



int main() {


short BUFF_MAX_SIZE = 1000;

    int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock < 0) {
        die_error();
    }

    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(5105);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    socklen_t client_size = sizeof(address);

    int is_binded = bind(sock, (struct sockaddr*) &address, sizeof(address));
    
    if (is_binded < 0) {
        die_error();
    }

    int status = listen(sock, 1);

    if (status < 0) {
        die_error();
    }

    int new_sock = accept(sock, (struct sockaddr*) &address, &client_size);


    if (new_sock >= 0) {
        char pre_buff[BUFF_MAX_SIZE];    
        int count = recv(new_sock, pre_buff, 100, 0);
        time(&t);
        //YEAR MONTH DAY HOUR MINUTE SECOND
        char output[BUFF_MAX_SIZE];

        struct tm* now = localtime(&t);

        sprintf(output, "%d-%d-%d %d:%d:%d:\t%s", now->tm_year + 1900, now->tm_mon, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, pre_buff);
        fputs(output, stdout);  
        strncpy(output, "a ", BUFF_MAX_SIZE);


    for (;;) {
      //  if ((accept(sock, (struct sockaddr*) &address, &client_size) < 0)) {
       //     die_error();         
       // }
        new_sock = accept(sock, (struct sockaddr*) &address, &client_size);
        char msg[BUFF_MAX_SIZE];
        int count = recv(new_sock, msg, BUFF_MAX_SIZE, 0);

        if (count < 0) {
            die_error();
        }

        time(&t);
        //YEAR MONTH DAY HOUR MINUTE SECOND

        struct tm* now = localtime(&t);

        sprintf(output, "%d-%d-%d %d:%d:%d:\t%s", now->tm_year + 1900, now->tm_mon, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, msg);
        fputs(output, stdout);
        strncpy(output, "", BUFF_MAX_SIZE);
        strncpy(msg, "", BUFF_MAX_SIZE);





        }
    }
    else {
        die_error();
    }


    return 0;
    

}