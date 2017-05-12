#ifndef CLIENT_H
#define CLIENT_H

#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <unistd.h>

#define SERVER "127.0.0.1"
#define BUFLEN 1024  //Max length of buffer
#define PORT 13651   //The port on which to send data

class Client
{
public:
    explicit Client();

private:
    struct sockaddr_in si_other;
    socklen_t slen;
    int sock_fd, i;
    char buf[BUFLEN];
    char message[BUFLEN];

    void init();
    void die (const char* str);
};

#endif // CLIENT_H
