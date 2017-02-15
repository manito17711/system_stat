#include "client.hpp"


Client::Client()
{
}

void Client::setServer(const Node& node)
{
    hp = gethostbyname(node.ipAddr.c_str());
    if (0 == hp)
    {
        // TODO: log error
        //std::cout << "ERROR: get server by name";

        close(sock);
        exit(1);
    }

    memcpy(&serverAddr.sin_addr, hp->h_addr, hp->h_length);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(node.port);
}

void Client::initSocket()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sock)
    {
        // TDOO: log error
        // std::cout << "ERROR: init socket.";
        // std::cout << strerror(errno) << std::endl;

        exit(1);
    }
}

bool Client::retrieveData()
{
    initSocket();

    if (connect(sock, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0)
    {
        // TODO: log error
        // std::cout << "ERROR: connecting to server..." << std::endl;
        // std::cout << strerror(errno) << std::endl;

        close(sock);
        return false;
    }

    int bufferSize = 1024;
    char buff[bufferSize];

    buff[0] = 'S';
    buff[1] = 'R';
    buff[2] = 'V';
    buff[3] = '\0';

    send(sock, buff, bufferSize, 0);
    recv(sock, buff, bufferSize, 0);

    report = std::__cxx11::string(buff);

    closeSocket();

    return true;
}

void Client::closeSocket()
{
    // TODO: check result, validate..

    close(sock);
    sock = -1; // set invalid data
}

std::__cxx11::string Client::getReport() const
{
    return report;
}
