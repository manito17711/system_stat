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
    std::function<void(int fd, ConnType type)> pFunc_onConn;
    std::size_t port;

    struct sockaddr_in si_in;
    struct sockaddr_in si_other;
    socklen_t si_other_len;
    int sock_fd;

    char buff[BUFF_SIZE];

    void init();
    ConnType defineConnectionType(const char* req); // define request - server or client

    bool favicon(const char* req);

public:
    explicit Server(std::size_t port);
    ~Server();

    int closeSocketDescr(int &fd);
    int closeServerSocketDescr();

    void startListen(std::size_t maxConn = 5);
    void sendData(int fd, const std::__cxx11::string& data);
    void setOnConn(std::function<void(int fd, ConnType type)> const &func);
};
