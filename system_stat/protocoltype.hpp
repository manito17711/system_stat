#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <netdb.h>
#include <memory>

#include <functional>
#include <connection_types.hpp>

class ProtocolType
{
public:
    ProtocolType(int port);
    virtual ~ProtocolType();

    virtual void initSocket() = 0;
    virtual void startListen() = 0;
    virtual int sendData(int fd, const std::__cxx11::string& data) = 0;
    virtual int readData(int fd, std::__cxx11::string& str) = 0;
    virtual std::shared_ptr<ProtocolType> createObject() = 0;


    int& getSockFd();
    const int& getPort() const;
    struct sockaddr_in& getSiLhs();
    socklen_t& getSiRhsLength();
    struct sockaddr_in& getSiRhs();

    void bindSocket();
    void setSiRhs(std::__cxx11::string ipAddr, int port);
    void setConnectionNonBlocking();
    void setOnConnection(std::function<void(int fd, ConnType type)> const &func);
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

private:
    struct hostent *hp;
};
