#include "protocoltypeudp.hpp"

ProtocolTypeUDP::ProtocolTypeUDP(int port) : ProtocolType(port) {}

void ProtocolTypeUDP::run()
{

}

void ProtocolTypeUDP::initSocketDescriptor()
{
    slen = sizeof(si_other);

    // create a UDP socket
    if (0 > (sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)))
    {
        // log error
        //exit(1);
    }


    // zero our the memory
    memset((char*) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);


    // bind socket
    if (0 > (bind(sock_fd, (struct sockaddr*) &si_me, sizeof(si_me))))
    {
        // log error
        //exit(1);
    }
}

