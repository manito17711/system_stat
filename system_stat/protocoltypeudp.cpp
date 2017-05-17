#include "protocoltypeudp.hpp"

ProtocolTypeUDP::ProtocolTypeUDP(int port) : ProtocolType(port) {}

void ProtocolTypeUDP::listen()
{

}

void ProtocolTypeUDP::initSocketDescriptor()
{
    slen = sizeof(si_rhs);

    // create a UDP socket
    if (0 > (sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)))
    {
        // log error
        //exit(1);
    }


    // zero our the memory
    memset((char*) &si_lhs, 0, sizeof(si_lhs));

    si_lhs.sin_family = AF_INET;
    si_lhs.sin_port = htons(port);
    si_lhs.sin_addr.s_addr = htonl(INADDR_ANY);


    // bind socket
    if (0 > (bind(sock_fd, (struct sockaddr*) &si_lhs, sizeof(si_lhs))))
    {
        // log error
        //exit(1);
    }
}

