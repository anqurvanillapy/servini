#include "../include/servini.h"

#include <string.h>

int
main(int argc, const char *argv[])
{
    pid_t pid;
    int listenfd, connfd;
    struct sockaddr_in servaddr;

    if (argc != 3) err_quit("usage: forkserver ip_address port\n");

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    servaddr.sin_port   = htons(atoi(argv[2]));

    printf("start serving on http://%s:%s ...\n", argv[1], argv[2]);

    Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    for (;;) {
        // Accept probably blocks.
        connfd = Accept(listenfd, (struct sockaddr *) NULL, NULL);

        // If it is the child process, handle the request.
        if ( (pid = Fork()) == 0) {
            // Child closes listening socket.
            Close(listenfd);

            // Print all the client input.
            while (read(connfd, buf, sizeof(buf)) > 0) fputs(buf, stdout);

            // Done with this client.
            Close(connfd);
            exit(0);
        }

        // Parent closes the connected socket.
        Close(connfd);
    }

    return 0;
}
