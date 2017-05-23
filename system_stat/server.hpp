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
#include "protocoltype.hpp"

class Server
{
private:
    std::function<void(int fd, ConnType type)> pFunc_onConn;
    std::shared_ptr<ProtocolType> protocol;   

    void init();

public:
    explicit Server(std::shared_ptr<ProtocolType> protocol);
    ~Server();

    int closeServerSocketDescr();

    void startListen();
    void sendData(int fd, const std::__cxx11::string& data);
    void setOnConn(std::function<void(int fd, ConnType type)> const &func);
};
