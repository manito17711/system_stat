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
    int sock;
    struct sockaddr_in serverAddr;
    socklen_t slen;
    struct hostent *hp;
    std::__cxx11::string report;

    void initSocket();
    void closeSocket();

public:
	explicit Client();

    void setServer(const Node&);
    bool retrieveData();
    std::__cxx11::string getReport() const;
};
