#include "dispatcher.hpp"

#define LOAD_TEST_SERVERS

Dispatcher::Dispatcher(Server *srv, Client *cln, Reporter *rpt, Network *ntw)
    : server(srv), client(cln), reporter(rpt), network(ntw)
{
}

void Dispatcher::run()
{
    std::cout << "1. Start listen.\n";
    std::cout << "2. Add server to network.\n";

    int i = 0;

#ifdef LOAD_TEST_SERVERS
    // 6 testing servers..
    for (int i = 140; i < 146; ++i)
    {
        std::string s = "192.168.194." + std::to_string(i);
        network->addServer(s, 13651);
    }

    std::cout << "6 testing servers imported.\n";
#endif

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
        client->collectAllReports();
        reporter->append(client->getReport());

        // we check all servers at the network and get their statistics

/*
        std::deque<std::unique_ptr<Client>> clients;
        std::deque<std::future<bool>> futuresReports;

        std::deque<void*> clients_vp;
        auto newClient = client->createObject();

        clients_vp.push_back(newClient);

        newClient->setServer(network->getServer(2));

#ifdef ASYNC_MODE
#ifdef PRINT_TIME
        auto start = std::chrono::system_clock::now();
#endif
        for (std::size_t i = 0; i < network->serversCount(); ++i)
        {
            std::unique_ptr<Client> cl (new Client());
            cl->setServer(network->getServer(i));

            futuresReports.push_back(std::async(std::launch::async, &Client::retrieveData, cl.get()));
            clients.push_back(std::move(cl));
        }

        for (std::size_t i = 0; i < futuresReports.size(); ++i)
        {
            reporter->append("\n");
            reporter->append(network->getServer(i).ipAddr);
            reporter->append(":  ");

            if (futuresReports[i].get())
            {
                reporter->append(clients[i]->getReport());
            }
            else
            {
                reporter->append("Error: No connection with server.");
            }
        }
#ifdef PRINT_TIME
        auto end = std::chrono::system_clock::now();
        auto elapsed = end - start;
        std::cout << elapsed.count() << std::endl;
#endif
#endif

#ifdef SYNC_MODE
#ifdef PRINT_TIME
        start = std::chrono::system_clock::now();
#endif
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
#ifdef PRINT_TIME
        end = std::chrono::system_clock::now();
        elapsed = end - start;
        std::cout << elapsed.count() << std::endl;
#endif
#endif
        reporter->setHTMLHeaders();
*/


        break;
    }
    case ConnType::server:

        // no actions nedded

        break;
    }

    server->sendData(fd, reporter->getReport());
}
