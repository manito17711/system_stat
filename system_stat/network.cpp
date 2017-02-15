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
    // TODO: check for duplication.. or switch to set

    servers.push_back(n);
}

Node& Network::getServer(std::size_t idx)
{
    return servers[idx];
}

std::size_t Network::serversCount() const
{
    return servers.size();
}

