#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFLEN 1024  //Max length of buffer

class Client
{
public:
    explicit Client(std::string server, int port);

private:
    const std::string SERVER;
    const int PORT;

    struct sockaddr_in si_other;
    socklen_t slen;
    int sock_fd, i;
    char buf[BUFLEN];
    char message[BUFLEN];

    void init();
    void die (const char* str);
};

#endif // CLIENT_H
