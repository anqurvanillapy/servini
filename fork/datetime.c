#include "../include/servini.h"

#include <string.h>
#include <time.h>

/// Serve the current server time.
void
handle_request(int connfd)
{
    // Server time string buffer.
    char buf[BUFSIZ];
    time_t ticks;
    
    ticks = time(NULL);
    // Simple HTTP/1.0 response mockup.
    snprintf(buf, sizeof(buf),
        "HTTP/1.0 200 OK\r\n\r\n%.24s\r\n", ctime(&ticks));
    Write(connfd, buf, strlen(buf));
    printf("[log] new request\n");
}

int
main(int argc, const char *argv[])
{
    pid_t pid;
    int listenfd, connfd;
    struct sockaddr_in servaddr;

    if (argc != 3) err_quit("usage: datetime ip_address port\n");

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

            // Handle the request.
            handle_request(connfd);

            // Done with this client.
            Close(connfd);
            exit(0);
        }

        // Parent closes the connected socket.
        Close(connfd);
    }

    return 0;
}
