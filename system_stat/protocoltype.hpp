#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


class ProtocolType
{
public:
    ProtocolType(int port);
    virtual ~ProtocolType();

    virtual void run() = 0;
    virtual void initSocketDescriptor() = 0;

    const int& getSockFd() const;
    const int& getPort() const;
    const int& getSiMeLen() const;
    const struct sockaddr_in& getSiMe() const;
    const struct sockaddr_in& getSiOther() const;

    int closeSocketFd();

protected:
    int sock_fd;
    int port;
    struct sockaddr_in si_me;
    struct sockaddr_in si_other;
    socklen_t slen;
};
