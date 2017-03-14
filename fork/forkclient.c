#include "../include/servini.h"
#include <strings.h>

int
main(int argc, const char *argv[])
{
    // User input buffer.
    char buf[BUFSIZ] = "";

    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 3) err_quit("usage: forkclient ip_address port");

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr)); // zeroes out the servaddr struct
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(atoi(argv[2]));
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    while (fgets(buf, sizeof(buf), stdin)) {
        Write(sockfd, buf, sizeof(buf));
    }

    Close(sockfd);

    return 0;
}
