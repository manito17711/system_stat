#include "client.hpp"


Client::Client(std::shared_ptr<ProtocolType> protocol, const Network* network) : protocol(protocol), network(network)
{

}



void Client::setServer(const Node& node)
{
    protocol->setSiRhs(node.ipAddr, node.port);
}



void Client::init()
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
    /*
    sock_fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // set connection non-blocking
    fcntl(sock_fd, F_SETFL, O_NONBLOCK);

    if (0 > sock_fd)
    {
        // TDOO: log error
        // std::cout << "ERROR: init socket.";
        // std::cout << strerror(errno) << std::endl;

        exit(1);
    }*/

    //protocol->init();
}



bool Client::retrieveData()
{
    protocol->initSocket();
    protocol->setConnectionNonBlocking();

    // send "SRV" to server - that is how we say to the server the request is not
    /*
    buff[0] = 'S';
    buff[1] = 'R';
    buff[2] = 'V';
    buff[3] = '\0';*/


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
    std::__cxx11::string data = "SRV";

    protocol->sendData(protocol->getSockFd(), data);

    // printf("%s\n", inet_ntoa(protocol->getSiRhs().sin_addr));

    sleep(1);

    auto received = protocol->readData(protocol->getSockFd(), data);

    if (-1 == received)
    {
        report = "";
        return false;
    }

    report = data;
    return true;
}



const std::__cxx11::string& Client::getReport() const
{
    return report;
}



void Client::collectAllReports()
{
    // we check all servers at the network and get their statistics

    report = "";

    std::deque<std::shared_ptr<Client>> clients;
    std::deque<std::future<bool>> futuresReports;


    for (std::size_t i = 0; i < network->serversCount(); ++i)
    {
        std::shared_ptr<Client> newClient (this->createObject());
        newClient->setServer(network->getServer(i));

        futuresReports.push_back(std::async(std::launch::async, &Client::retrieveData, newClient.get()));
        clients.push_back(newClient);
    }

    for (std::size_t i = 0; i < futuresReports.size(); ++i)
    {
        report += "\n";
        report += network->getServer(i).ipAddr;
        report += ":  ";

        if (futuresReports[i].get())
        {
            report += clients[i]->getReport();
        }
        else
        {
            report += "Error: No connection with server.";
        }
    }
}



std::shared_ptr<Client> Client::createObject()
{
    std::shared_ptr<Client> newObj (new Client(protocol->createObject(), network));

    return newObj;
}
