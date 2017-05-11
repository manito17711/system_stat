#include "server.hpp"


Server::Server(std::size_t port) : port(port)
{
    init();
}

Server::~Server()
{
    // TDOO: check if return -1 and log...

    closeServerSocketDescr();
}

void Server::sendData(int fd, const std::__cxx11::string& data)
{
    send(fd, data.c_str(), strlen(data.c_str()), 0);
}

void Server::startListen(std::size_t maxConn)
{
    if (0 == listen(serverSock, maxConn))
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

        int clientSock = accept(serverSock, (struct sockaddr*) &addr, &addrlen);
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
}

ConnType Server::defineConnectionType(const char* req)
{
    int l = strlen(req);
    if (3 > l)
    {
        // TODO: log error
        exit(1);
    }

    std::__cxx11::string firstThree = std::__cxx11::string(req).substr(0, 3);

    ConnType t = firstThree.compare("SRV") ? ConnType::client : ConnType::server;

    return t;
}

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
    pFunc_onConn = func;
}

int Server::closeServerSocketDescr()
{
    return closeSocketDescr(serverSock);
}

int Server::closeSocketDescr(int &fd)
{
    int r = close(fd);
    fd = -1; // set invalid data on file descriptor

    return r;
}

void Server::init()
{
    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > serverSock)
    {
        // TODO: log on error
        // std::cout << "ERROR: socket - cannot create an endpoint for communication!" << std::endl;

        exit(1);
    }

    // set socket to be reused
    int enable = 1;
    if (0 > setsockopt(serverSock, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)))
    {
        // TDOD: log error in set socket reuse..
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (0 > bind(serverSock, (struct sockaddr*) &serverAddr, sizeof(serverAddr)))
    {
        // TODO: log on error
        // cout << strerror(errno) << endl;

        if (-1 != serverSock)
        {
            close(serverSock);
        }

        exit(1);
    }

    std::cout << "Server initialized" << std::endl;
}
