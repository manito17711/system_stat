#include "network.hpp"

//#define LOAD_TEST_SERVERS

Network::Network()
{
#ifdef LOAD_TEST_SERVERS
    // 6 testing servers..
    for (int i = 140; i < 146; ++i)
    {
        std::string s = "192.168.194." + std::to_string(i);
        addServer(s, 13651);
    }

    std::cout << "6 testing servers imported.\n";
#endif
}

void Network::addServer(std::__cxx11::string ipAddr, std::size_t port)
{
    // TODO: validate address and port

    addServer(Node(ipAddr, port));
}

void Network::addServer(const Node& n)
{
    for (std::size_t i = 0; i < servers.size(); ++i)
    {
        if (n.ipAddr == servers[i].ipAddr)
            return;
    }

    servers.push_back(n);
}

const Node& Network::getServer(std::size_t idx) const
{
    return servers[idx];
}

std::size_t Network::serversCount() const
{
    return servers.size();
}

