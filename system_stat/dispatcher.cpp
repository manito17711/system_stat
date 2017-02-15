#include "dispatcher.hpp"


Dispatcher::Dispatcher(Server *srv, Client *cln, Reporter *rpt, Network *ntw)
    : server(srv), client(cln), reporter(rpt), network(ntw)
{
}

void Dispatcher::run()
{
    std::cout << "1. Start listen.\n";
    std::cout << "2. Add server to network.\n";

    int i = 0;

    do
    {
        std::cout << "-------------------------\n";
        std::cout << "Select option: ";
        std::cin >> i;
        switch (i)
        {
        case 1:
            break;
        case 2:
        {
            std::__cxx11::string ip;
            std::size_t port;

            std::cout << "Ip: ";
            std::cin >> ip;

            std::cout << "Port: ";
            std::cin >> port;

            network->addServer(ip, port);
            break;
        }
        default:
            std::cout << "Invalid input\n";
            break;
        }
    } while (1 != i);

    server->setOnConn([this](int fd, ConnType type){ onConnection(fd, type); });
    server->startListen();
}

void Dispatcher::onConnection(int fd, ConnType type)
{
    reporter->initReport(type);

    switch (type)
    {
    case ConnType::client:
    {
        // we check all servers at the network and get their statistics

        for (std::size_t i = 0; i < network->serversCount(); ++i)
        {
            Node n = network->getServer(i);
            client->setServer(n);

            reporter->append("<br>");
            reporter->append("-------------------------------------------");
            reporter->append("<br>");
            reporter->append(n.ipAddr);
            reporter->append("<br>");

            if (client->retrieveData())
            {
                reporter->append(client->getReport());
            }
            else
            {
                reporter->append("Error: No connection with server.");
            }            
        }

        reporter->setHTMLHeaders();
        break;
    }
    case ConnType::server:

        // no actions nedded

        break;
    }

    server->sendData(fd, reporter->getReport());
    //server->closeSocketDescr(fd);
}
