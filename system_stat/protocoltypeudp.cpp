#include "protocoltypeudp.hpp"

ProtocolTypeUDP::ProtocolTypeUDP(int port) : ProtocolType(port) {}

void ProtocolTypeUDP::listen()
{
    for (;;)
    {
        clearBuff();

        si_rhs_len = sizeof(si_rhs);        
        const ssize_t received = recvfrom(sock_fd, buff, buff_size, 0, (struct sockaddr*) &si_rhs, &si_rhs_len);

        if (received > 0)
        {
            ConnType type = defineConnectionType(buff);
            pFunc_onConn(sock_fd, type);
        }
        else
        {
            // TODO: log error
            // std::cerr << "Error: recvfrom() --errno: " << strerror(errno) << std::endl;
            exit(1);
        }
    }
}

void ProtocolTypeUDP::init()
{
    si_rhs_len = sizeof (si_rhs);

    // create a UDP socket
    if (0 > (sock_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)))
    {
        // TODO: log error
        exit(1);
    }


    // zero our the memory
    memset((char*) &si_lhs, 0, sizeof(si_lhs));

    si_lhs.sin_family = AF_INET;
    si_lhs.sin_port = htons(port);
    si_lhs.sin_addr.s_addr = htonl(INADDR_ANY);


    // bind socket
    if (0 > (bind(sock_fd, (struct sockaddr*) &si_lhs, sizeof(si_lhs))))
    {
        // TODO: log error
        exit(1);
    }
}

int ProtocolTypeUDP::sendData(int fd, const std::__cxx11::string &data)
{
    int send_data = sendto(fd, data.c_str(), strlen(data.c_str()), 0, (struct sockaddr *) &(si_rhs), si_rhs_len);

    return send_data;
}

int ProtocolTypeUDP::sendData(int fd, const std::__cxx11::string &data, sockaddr_in server)
{
    si_rhs = server;
    si_rhs_len = sizeof (si_rhs);

    sendData(fd, data);
}

int ProtocolTypeUDP::readData(int fd, std::__cxx11::string &str)
{
    clearBuff();

    const ssize_t received = recvfrom(sock_fd, buff, buff_size, 0, (struct sockaddr*) &si_rhs, &si_rhs_len);

    if (-1 == received)
    {
        str = strerror(errno);
    }
    else
    {
        str = buff;
    }

    return received;
}

