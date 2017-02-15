#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <functional>
#include <errno.h>
#include <iostream>

#include "connection_types.hpp"

class Server
{
private:
    std::function<void(int fd, ConnType type)> pFunc_onConn;
    std::size_t port;

    struct sockaddr_in serverAddr;
    int serverSock;

    void init();
    ConnType defRequestType(const char* req);

    bool favicon(const char* req);

public:
    explicit Server(std::size_t port);
    ~Server();

    int closeSocketDescr(int &fd);
    int closeServerSocketDescr();

    void startListen(std::size_t max_conn = 5);
    void sendData(int fd, const std::__cxx11::string &data);
    void setOnConn(std::function<void(int fd, ConnType type)> const &func);
};