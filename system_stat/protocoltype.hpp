#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <memory>

#include <functional>
#include <connection_types.hpp>

class ProtocolType
{
public:
    ProtocolType(int port);
    virtual ~ProtocolType();

    virtual void init() = 0;
    virtual void listen() = 0;
    virtual int sendData(int fd, const std::__cxx11::string& data) = 0;
    virtual int sendData(int fd, const std::__cxx11::string &data, sockaddr_in server) = 0;
    virtual int readData(int fd, std::__cxx11::string& str) = 0;
    virtual std::shared_ptr<ProtocolType> createObject() = 0;


    const int& getSockFd() const;
    const int& getPort() const;
    const socklen_t& getSiLhsLength() const;
    const struct sockaddr_in& getSiLhs() const;
    const struct sockaddr_in& getSiRhs() const;


    void setOnConn(std::function<void(int fd, ConnType type)> const &func);
    int closeSocketFd();

protected:
    int sock_fd;
    int port;
    struct sockaddr_in si_lhs;
    struct sockaddr_in si_rhs;
    socklen_t si_rhs_len;

    static const size_t buff_size = 1024;
    char buff[buff_size];
    std::function<void(int, ConnType)> pFunc_onConn; // TODO: this definition should be in separate file.. copied from server.hpp

    ConnType defineConnectionType(const char* req); // define request - server or client.

    void clearBuff();
};
