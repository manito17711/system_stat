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

const socklen_t& ProtocolType::getSiLhsLength() const
{
    return si_rhs_len;
}

const sockaddr_in& ProtocolType::getSiLhs() const
{
    return si_lhs;
}

const sockaddr_in& ProtocolType::getSiRhs() const
{
    return si_rhs;
}

void ProtocolType::setOnConn(const std::function<void (int, ConnType)> &func)
{
    pFunc_onConn = func;
}

int ProtocolType::closeSocketFd()
{
    int result = close(sock_fd);
    sock_fd = -1; // set invalid data on file descriptor

    return result;
}

ConnType ProtocolType::defineConnectionType(const char* req)
{
    int l = strlen(req);
    if (3 > l)
    {
        // TODO: log error
        exit(1);
    }

    std::__cxx11::string firstThree = std::__cxx11::string(req).substr(0, 3);

    ConnType t = firstThree.compare("SRV") ? ConnType::client : ConnType::server;

    return t;
}

void ProtocolType::clearBuff()
{
    memset(buff, 0, buff_size);
}

