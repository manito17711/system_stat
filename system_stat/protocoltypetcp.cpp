#include "protocoltypetcp.hpp"
#include <iostream>
#include <fcntl.h>


ProtocolTypeTCP::ProtocolTypeTCP(int port) : ProtocolType(port)
{

}



void ProtocolTypeTCP::startListen()
{
    static const int MAX_CONNECTION = 5;

    if (0 == listen(sock_fd, MAX_CONNECTION))
    {
        std::cout << "Server listen on port " << port << std::endl;
    }
    else
    {
        // TODO: log error
        //std::cout << strerror(errno) << std::endl;

        exit(1);
    }

    for (;;)
    {
        si_rhs_len = sizeof(si_rhs);
        ssize_t received = 0;

        int clientSock = accept(sock_fd, (struct sockaddr*) &si_rhs, &si_rhs_len);
        if (-1 != clientSock)
        {
            clearBuff();

            received = read(clientSock, buff, buff_size);
            ConnType type = defineConnectionType(buff);

            if (!favicon(buff))
            {
                std::cout << "Incoming call: " << inet_ntoa(si_rhs.sin_addr) << " Type: ";
                (type == ConnType::client) ? std::cout << "client\n" : std::cout << "server\n";

                pFunc_onConn(clientSock, type);
            }
        }
        else
        {
            // TODO: log error
        }

        close (clientSock);
    }
}



void ProtocolTypeTCP::initSocket()
{
    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (0 > sock_fd)
    {
        // TDOO: log error
        // std::cout << "ERROR: init socket.";
        // std::cout << strerror(errno) << std::endl;

        exit(1);
    }

    // zero our the memory
    memset((char*) &si_lhs, 0, sizeof(si_lhs));

    si_lhs.sin_family = AF_INET;
    si_lhs.sin_port = htons(port);
    si_lhs.sin_addr.s_addr = htonl(INADDR_ANY);
}



int ProtocolTypeTCP::sendData(int fd, const std::__cxx11::string &data)
{
    if (data.compare("SRV") == 0)
    {
        // set descriptior to non-blocking... todo: try to avoid fcntl
        int flags = fcntl(fd, F_GETFL);
        if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
        {
            std::cout << "Err: fcntl\n";
        }

        if (0 > connect(fd, (struct sockaddr*) &si_rhs, si_rhs_len))
        {
            // TODO: log error
            // std::cout << "ERROR: connecting to server..." << std::endl;
            // std::cout << strerror(errno) << std::endl;

            //return false;
        }
    }

    return send(fd, data.c_str(), data.length(), 0);
}



int ProtocolTypeTCP::readData(int fd, std::__cxx11::string &report)
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
        report = "Timeout! No data in 1 second!\0";
        received = strlen(buff);
    }
    else
    {
        received = recv(fd, buff, buff_size, 0);
        if (-1 == received)
        {
            report = "recvfrom() return -1\n\0";
        }
        else
        {
            report = buff;
        }
    }

    return received;
}



std::shared_ptr<ProtocolType> ProtocolTypeTCP::createObject()
{
    std::shared_ptr<ProtocolType> newObj (new ProtocolTypeTCP(port));
    return newObj;
}



bool ProtocolTypeTCP::favicon(const char *req)
{
    std::__cxx11::string r = std::__cxx11::string(req).substr(0, 12);
    std::__cxx11::string favicon ("GET /favicon");

    if (0 == r.compare(favicon))
    {
        return true;
    }

    return false;
}
