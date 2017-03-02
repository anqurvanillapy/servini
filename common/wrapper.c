#include "servini.h" // TODO

void
Inet_pton(int af, const char *src, void *dst)
{
    if (inet_pton(af, src, dst) <= 0)
        err_quit("invalid address");
}

int
Socket(int familiy, int type, int protocol)
{
    int n;

    if ( (n = socket(familiy, type, protocol)) < 0)
        err_sys("socket error");

    return n;
}

void
Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    if (bind(sockfd, addr, addrlen) < 0)
        err_sys("bind error");
}

void
Listen(int sockfd, int backlog)
{
    if (listen(sockfd, backlog) < 0)
        err_sys("listen error");
}

int
Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int n;

    if ( (n = accept(sockfd, addr, addrlen)) < 0)
        err_sys("accept error");
    
    return n;
}

void
Write(int fd, const void *buf, size_t count)
{
    if (write(fd, buf, count) < 0)
        err_sys("write error");
}

void
Close(int fd)
{
    if (close(fd) < 0)
        err_sys("close error");
}
