#include "protocoltype.hpp"

ProtocolType::ProtocolType()
{
}

ProtocolType::~ProtocolType()
{
}

int ProtocolType::closeSocketDescriptor()
{
    int result = close(socket_fd);
    socket_fd = -1; // set invalid data on file descriptor

    return result;
}

