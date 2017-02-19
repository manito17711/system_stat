#include "network.hpp"



Network::Network()
{
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

void Network::checkOnlineServers()
{

}

void Network::isOnline()
{

}


Node& Network::getServer(std::size_t idx)
{
    return servers[idx];
}

std::size_t Network::serversCount() const
{
    return servers.size();
}

