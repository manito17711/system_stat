#include "protocoltype.hpp"

ProtocolType::ProtocolType(int port) : port(port) {}


ProtocolType::~ProtocolType()
{
    if (-1 == sock_fd)
    {
        closeSocketFd();
    }
}

const int &ProtocolType::getSockFd() const
{
    return sock_fd;
}

const int &ProtocolType::getPort() const
{
    return port;
}

const int &ProtocolType::getSiLhsLength() const
{
    return slen;
}

const sockaddr_in& ProtocolType::getSiLhs() const
{
    return si_me;
}

const sockaddr_in& ProtocolType::getSiRhs() const
{
    return si_other;
}


int ProtocolType::closeSocketFd()
{
    int result = close(sock_fd);
    sock_fd = -1; // set invalid data on file descriptor

    return result;
}

