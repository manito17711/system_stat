#include "protocoltypeudp.hpp"



ProtocolTypeUDP::ProtocolTypeUDP(int port) : ProtocolType(port)
{

}



void ProtocolTypeUDP::startListen()
{    
    for (;;)
    {
        clearBuff();

        si_rhs_len = sizeof(si_rhs);        
        const ssize_t received = recvfrom(sock_fd, buff, buff_size, 0, (struct sockaddr*) &si_rhs, &si_rhs_len);

        if (!fork())
        {
            printf("%s\n", buff);


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

            exit(0);
        }
        else
        {
            // TODO: log fork error
        }
    }
}



void ProtocolTypeUDP::initSocket()
{
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

}



int ProtocolTypeUDP::sendData(int fd, const std::__cxx11::string &data)
{
    si_rhs_len = sizeof (si_rhs);
    int send_data = sendto(fd, data.c_str(), strlen(data.c_str()), 0, (struct sockaddr *) &(si_rhs), si_rhs_len);

    return send_data;
}



int ProtocolTypeUDP::readData(int fd, std::__cxx11::string &str)
{
    clearBuff();

    pfd.fd = sock_fd;
    pfd.events = POLLIN;

    pfd_rv = poll(&pfd, 1, pfd_tv);
    ssize_t received = -1;
    if (-1 == pfd_rv)
    {
        // TODO: poll return error
        exit(1);
    }
    else if (0 == pfd_rv)
    {
        strcpy(buff, "Timeout! No data in 2 seconds!\n\0");
        received = strlen(buff);
    }
    else
    {
        received = recvfrom(fd, buff, buff_size, 0, (struct sockaddr*) &si_rhs, &si_rhs_len);
        if (-1 == received)
        {
            strcpy(buff, "recvfrom() return -1\n\0");
            received = strlen(buff);
        }
    }


    /*const ssize_t received = recvfrom(fd, buff, buff_size, 0, (struct sockaddr*) &si_rhs, &si_rhs_len);

    if (-1 == received)
    {
        str = strerror(errno);
    }
    else
    {
        str = buff;
    }*/

    return received;
}



std::shared_ptr<ProtocolType> ProtocolTypeUDP::createObject()
{
    std::shared_ptr<ProtocolType> newObj (new ProtocolTypeUDP(port));
    return newObj;
}

