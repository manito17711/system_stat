#pragma once

#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

#include "node.hpp"

class Client
{
private:
    static const size_t BUFF_SIZE = 1024;

    char buff[BUFF_SIZE];
    int sock_fd;
    struct sockaddr_in srv_rhs;
    socklen_t slen;
    struct hostent *hp;
    std::__cxx11::string report;

    void initSocket();
    void closeSocket();

public:
	explicit Client();

    void setServer(const Node&);
    bool retrieveData();
    const std::__cxx11::string& getReport() const;
};
