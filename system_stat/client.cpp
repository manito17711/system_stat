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

    slen = sizeof(serverAddr);
}

void Client::initSocket()
{
    // tcp
    /*
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sock)
    {
        // TDOO: log error
        // std::cout << "ERROR: init socket.";
        // std::cout << strerror(errno) << std::endl;

        exit(1);
    }
    */

    // udp
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    fcntl(sock, F_SETFL, O_NONBLOCK);
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

    // tcp
    /*
    if (0 > connect(sock, (struct sockaddr*) &serverAddr, sizeof(serverAddr)))
    {
        // TODO: log error
        // std::cout << "ERROR: connecting to server..." << std::endl;
        // std::cout << strerror(errno) << std::endl;

        closeSocket();
        return false;
    }
    */

    // udp

    int bufferSize = 1024;
    char buff[bufferSize];

    buff[0] = 'S';
    buff[1] = 'R';
    buff[2] = 'V';
    buff[3] = '\0';

    sendto(sock, buff, 3, 0, (struct sockaddr *) &serverAddr, slen);
    printf("%s\n", inet_ntoa(serverAddr.sin_addr));

    sleep(1);

    auto received = recvfrom(sock, buff, bufferSize, 0, (struct sockaddr *) &serverAddr, &slen);

    if (-1 == received)
    {
        closeSocket();
        return false;
    }

    //send(sock, buff, bufferSize, 0);
    //recv(sock, buff, bufferSize, 0);

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
