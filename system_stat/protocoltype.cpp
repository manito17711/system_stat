#include "protocoltype.hpp"

ProtocolType::ProtocolType(int port) : port(port) {}


ProtocolType::~ProtocolType()
{
    if (-1 == sock_fd)
    {
        closeSocketFd();
    }
}

int &ProtocolType::getSockFd()
{
    return sock_fd;
}

const int &ProtocolType::getPort() const
{
    return port;
}

sockaddr_in& ProtocolType::getSiLhs()
{
    return si_lhs;
}

socklen_t &ProtocolType::getSiRhsLength()
{
    return si_rhs_len;
}

sockaddr_in& ProtocolType::getSiRhs()
{
    return si_rhs;
}

void ProtocolType::bindSocket()
{
    if (0 > (bind(sock_fd, (struct sockaddr*) &si_lhs, sizeof(si_lhs))))
    {
        // TODO: log error
        exit(1);
    }
}

void ProtocolType::setSiRhs(std::__cxx11::string ipAddr, int port)
{
    hp = gethostbyname(ipAddr.c_str());
    if (0 == hp)
    {
        // TODO: log error
        // std::cout << "ERROR: get server by name";

        exit(1);
    }

    memcpy(&si_rhs.sin_addr, hp->h_addr, hp->h_length);
    si_rhs.sin_family = AF_INET;
    si_rhs.sin_port = htons(port);

    si_rhs_len = sizeof(si_rhs);
}



void ProtocolType::setConnectionNonBlocking()
{
    // set connection non-blocking
    fcntl(sock_fd, F_SETFL, O_NONBLOCK);
}



void ProtocolType::setSocketReusable()
{
    // set socket reusable
    int enable = 1;
    if (0 > setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)))
    {
        // TDOD: log error in set socket reuse..
    }
}



void ProtocolType::setOnConnection(const std::function<void (int, ConnType)> &func)
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
