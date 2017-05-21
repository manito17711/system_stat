#include "server.hpp"
#include "errno.h"

Server::Server(std::shared_ptr<ProtocolType> protocol) : protocol(protocol)
{
    init();
}



Server::~Server()
{
    if (protocol->getSockFd() != -1)
    {
        protocol->closeSocketFd();
    }
}



void Server::sendData(int fd, const std::__cxx11::string& data)
{
    // tcp
    //send(fd, data.c_str(), strlen(data.c_str()), 0);


    // udp
    /*
    sendto(sock_fd, data.c_str(), strlen(data.c_str()), 0, (struct sockaddr *) &(si_rhs), si_rhs_len);
    std::cout << "data to send: " << data << std::endl;*/

    protocol->sendData(fd, data);
}



void Server::startListen(std::size_t maxConn)
{
    // tcp
    /*
    if (0 == listen(sock_fd, maxConn))
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
        struct sockaddr_in addr;
        socklen_t addrlen = sizeof(addr);
        ssize_t received = 0;

        int clientSock = accept(sock_fd, (struct sockaddr*) &addr, &addrlen);
        if (-1 != clientSock)
        {
            int buffSize = 1024;
            char buff[buffSize];

            received = read(clientSock, buff, buffSize);
            ConnType type = defineConnectionType(buff);

            if (!favicon(buff))
            {
                std::cout << "Incoming call: " << inet_ntoa(addr.sin_addr) << " Type: ";
                (type == ConnType::client) ? std::cout << "client\n" : std::cout << "server\n";

                pFunc_onConn(clientSock, type);
            }
        }
        else
        {
            // TODO: log error
        }

        closeSocketDescr(clientSock);
    }
    */


    // udp
    /*
    for (;;)
    {
        clearBuff();

        si_rhs_len = sizeof(si_rhs);
        const ssize_t received = recvfrom(sock_fd, buff, BUFF_SIZE, 0, (struct sockaddr*) &si_rhs, &si_rhs_len);
        std::cout << buff << std::endl;

        if (received > 0)
        {
            std::cout << "Incoming call: " << inet_ntoa(si_rhs.sin_addr) << " Type: ";

            ConnType type = defineConnectionType(buff);
            (type == ConnType::client) ? std::cout << "client\n" : std::cout << "server\n";

            pFunc_onConn(sock_fd, type);
        }
        else
        {
            std::cout << "Error: recvfrom() --errno: " << strerror(errno) << std::endl;
        }
    }*/

    protocol->listen();
}


// should go in TCP file
bool Server::favicon(const char* req)
{
    std::__cxx11::string r = std::__cxx11::string(req).substr(0, 12);
    std::__cxx11::string favicon ("GET /favicon");

    if (0 == r.compare(favicon))
    {
        return true;
    }

    return false;
}



void Server::setOnConn(std::function<void(int fd, ConnType type)> const &func)
{
    protocol->setOnConnection(func);
    //pFunc_onConn = func;
}



int Server::closeServerSocketDescr()
{
    return protocol->closeSocketFd();
}



void Server::init()
{
    // tcp
    /*
    sock_fd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (0 > sock_fd)
    {
        // TODO: log on error
        // std::cout << "ERROR: socket - cannot create an endpoint for communication!" << std::endl;

        exit(1);
    }

    // set socket to be reused
    int enable = 1;
    if (0 > setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)))
    {
        // TDOD: log error in set socket reuse..
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (0 > bind(sock_fd, (struct sockaddr*) &serverAddr, sizeof(serverAddr)))
    {
        // TODO: log on error
        // cout << strerror(errno) << endl;

        if (-1 != sock_fd)
        {
            close(sock_fd);
        }

        exit(1);
    }
    */

    // set socket to be reused


    /*
    // udp
    sock_fd = socket (PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (0 > sock_fd)
    {
        // TODO: log on error
        // std::cout << "ERROR: socket()" << std::endl;

        exit(1);
    }

    // set socket reusable
    int enable = 1;
    if (0 > setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)))
    {
        // TDOD: log error in set socket reuse..
    }

    // init variable
    si_lhs.sin_family = AF_INET;
    si_lhs.sin_addr.s_addr = INADDR_ANY;
    si_lhs.sin_port = htons(PORT);

    if (0 > bind(sock_fd, (struct sockaddr*) &si_lhs, sizeof(si_lhs)))
    {
        // TODO: log on error
        // cout << strerror(errno) << endl;

        if (-1 != sock_fd)
        {
            close (sock_fd);
        }

        exit(1);
    }
    */

    protocol->initSocket();
    protocol->bindSocket();

    std::cout << "Server initialized" << std::endl;
}
