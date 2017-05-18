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

        close(sock_fd);
        exit(1);
    }

    memcpy(&srv_rhs.sin_addr, hp->h_addr, hp->h_length);
    srv_rhs.sin_family = AF_INET;
    srv_rhs.sin_port = htons(node.port);

    slen = sizeof(srv_rhs);
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
    sock_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // set connection non-blocking
    fcntl(sock_fd, F_SETFL, O_NONBLOCK);

    if (0 > sock_fd)
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

    // send "SRV" to server - that is how we say to the server the request is not
    buff[0] = 'S';
    buff[1] = 'R';
    buff[2] = 'V';
    buff[3] = '\0';


    // tcp
    /*
    if (0 > connect(sock_fd, (struct sockaddr*) &srv_rhs, slen))
    {
        // TODO: log error
        // std::cout << "ERROR: connecting to server..." << std::endl;
        // std::cout << strerror(errno) << std::endl;

        closeSocket();
        return false;
    }   

    send(sock, buff, BUFF_SIZE, 0);
    recv(sock, buff, BUFF_SIZE, 0);
    */


    // udp

    sendto(sock_fd, buff, 3, 0, (struct sockaddr *) &srv_rhs, slen);
    printf("%s\n", inet_ntoa(srv_rhs.sin_addr));

    // wait for 1 second so servers can respond
    sleep(1);

    // after one second, we pull the report
    // if server is not ready for 1 second, we return false and go forward
    auto received = recvfrom(sock_fd, buff, BUFF_SIZE, 0, (struct sockaddr *) &srv_rhs, &slen);

    if (-1 == received)
    {
        closeSocket();
        return false;
    }

    report = std::__cxx11::string(buff);

    closeSocket();
    return true;
}

const std::__cxx11::string& Client::getReport() const
{
    return report;
}

void Client::closeSocket()
{
    // TODO: check result, validate..

    close(sock_fd);
    sock_fd = -1; // set invalid data
}
