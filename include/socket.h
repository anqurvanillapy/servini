#ifndef __servini__socket_h
#define __servini__socket_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 4096    /* max text line length */
#define LISTENQ 20      /* max listen queue */

#define err_quit(errmsg) do {   \
    fputs(errmsg, stdout);      \
    exit(EXIT_FAILURE);         \
} while(0)

#define err_sys(errmsg) do {    \
    perror(errmsg);             \
    exit(EXIT_FAILURE);         \
} while(0)

void  Inet_pton(int af, const char *src, void *dst);
int   Socket(int family, int type, int protocol);
void  Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void  Listen(int sockfd, int backlog);
int   Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
void  Write(int fd, const void *buf, size_t count);
void  Close(int fd);

#endif // !__servini__socket_h
