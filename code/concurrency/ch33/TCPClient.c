#include <stdio.h>
#include <stdlib.h>         // perror(), exit(), atoi()
#include <sys/types.h>      // see NOTES in man 2 socket
#include <sys/socket.h>     // socket(), connect(), send(), recv(), AF_INET, SOCK_STREAMs
#include <netinet/in.h>     // sockaddr_in, INADDR_ANY
#include <string.h>         // memset(), strlen()
#include <arpa/inet.h>      // htons(), inet_addr()
#include <unistd.h>         // read(), close()
#include <fcntl.h>          // open()

#define BUFFSIZE    1024
#define PORT        8080
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[]) {
    int sleep_seconds;
    if (argc != 3) {
        printf("Usage: ./TCPClient.out sleep_seconds file_path\n");
        exit(EXIT_FAILURE);
    } else {
        sleep_seconds = atoi(argv[1]);
    }
    int sfd;
    struct sockaddr_in server_addr;                         // man 7 ip
    sfd = socket(AF_INET, SOCK_STREAM, 0);                  // tcp socket
    if (sfd == -1)
        handle_error("socket");

    memset(&server_addr, 0, sizeof(struct sockaddr_in));    // clear structure
    server_addr.sin_family      = AF_INET;                  // address family, IPV4
    server_addr.sin_port        = htons(PORT);              // port in network byte order
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");   // internet address

    sleep(sleep_seconds);
    if (connect(sfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in)) != 0)
        handle_error("connect");

    char buff[BUFFSIZE];
    memset(buff, 0, BUFFSIZE);
    strncpy(buff, argv[2], strlen(argv[2]));
    printf("Request file contents: %s\n", buff);
    if (send(sfd, buff, strlen(buff), 0) == -1)
        handle_error("send");

    memset(buff, 0, BUFFSIZE);
    if (recv(sfd, buff, BUFFSIZE, 0) == -1)
        handle_error("recv");
    printf("From server: %s\n", buff);
    close(sfd);
    return 0;
}