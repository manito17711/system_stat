#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class ProtocolType
{
public:
    ProtocolType();
    virtual ~ProtocolType();

    virtual int initSocketDescriptor() = 0;
    int closeSocketDescriptor();

protected:
    int socket_fd;
    struct sockaddr_in serverAddr;

};
