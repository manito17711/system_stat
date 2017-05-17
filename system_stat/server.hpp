#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <functional>
#include <errno.h>
#include <iostream>

#include "connection_types.hpp"

const int BUFF_SIZE = 1024;

class Server
{
private:
    const std::size_t PORT;
    std::function<void(int fd, ConnType type)> pFunc_onConn;

    struct sockaddr_in si_lhs;
    struct sockaddr_in si_rhs;
    socklen_t si_rhs_len;
    int sock_fd;

    char buff[BUFF_SIZE];

    void init();
    ConnType defineConnectionType(const char* req); // define request - server or client

    bool favicon(const char* req); // this should not be here!!!
    void clearBuff();

public:
    explicit Server(std::size_t port);
    ~Server();

    int closeSocketDescr(int &fd); // TODO: try to remove?
    int closeServerSocketDescr();

    void startListen(std::size_t maxConn = 5); // max conn = 5 - only for TCP connection..
    void sendData(int fd, const std::__cxx11::string& data);
    void setOnConn(std::function<void(int fd, ConnType type)> const &func);
};
