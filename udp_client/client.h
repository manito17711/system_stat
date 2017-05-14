#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>

class Client
{
public:
    explicit Client(std::__cxx11::string server, int port);

private:
    static const size_t BUFF_SIZE = 1024;

    const std::__cxx11::string SERVER;
    const int PORT;

    struct sockaddr_in si_other;
    socklen_t slen;
    int sock_fd, i;
    char buff[BUFF_SIZE];
    char message[BUFF_SIZE];

    void init();
};

#endif // CLIENT_H
