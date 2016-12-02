#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 4096  /* max text line length */

#define err_quit(errmsg) do {   \
    fputs(errmsg, stdout);      \
    exit(EXIT_FAILURE);         \
}

#define err_sys(errmsg) do {    \
    perror(errmsg);             \
    exit(EXIT_FAILURE);         \
}

int
main(int argc, const char *argv[])
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if (argc != 2)
        err_quit("not enough arguments\n");

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    bzero(&servaddr, sizeof(servaddr)); // like memset, filling w/ 0s
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(80);

    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        err_quit("%s: int_pton error", argv[1]);

    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("connection error");

    while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;    /* null terminator */
        if (fputs(recvline, stdout) == EOF)
            err_sys("fputs error");
    }

    if (n < 0)
        err_sys("read error");

    return 0;
}
