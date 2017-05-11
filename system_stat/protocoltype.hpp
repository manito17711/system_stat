#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class ProtocolType
{
public:
    ProtocolType();
    virtual ~ProtocolType();

protected:
    int socket_fd;

};
