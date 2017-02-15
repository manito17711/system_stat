#pragma once

#include <string>
#include <vector>

#include "node.hpp"

class Network
{
private:
    std::__cxx11::string dir;
    std::__cxx11::string fileName;
    std::vector<Node> servers;

public:
    explicit Network();

    void addServer(std::string ipAddr, std::size_t port);
    void addServer(const Node& n);

    Node& getServer(std::size_t idx);
    std::size_t serversCount() const;
};

