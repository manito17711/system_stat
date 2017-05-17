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

    virtual void init() = 0;
    virtual void listen() = 0;

    const int& getSockFd() const;
    const int& getPort() const;
    const socklen_t& getSiLhsLength() const;
    const struct sockaddr_in& getSiLhs() const;
    const struct sockaddr_in& getSiRhs() const;

    int closeSocketFd();

protected:
    int sock_fd;
    int port;
    struct sockaddr_in si_lhs; // TODO: unused parameter ?!
    struct sockaddr_in si_rhs;
    socklen_t slen;

    void clearBuff();
    virtual void initSocketDescriptor() = 0;
};
