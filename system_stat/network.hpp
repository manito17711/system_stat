#pragma once

#include <string>
#include <deque>

#include "node.hpp"

class Network
{
private:
    // TODO: write all servers to file and load data from there
    std::__cxx11::string dir;       // working directory
    std::__cxx11::string fileName;  // file with servers data - ip, port, etc...

    std::deque<Node> servers;

public:
    explicit Network();

    void addServer(std::string ipAddr, std::size_t port);
    void addServer(const Node& n);

    // TODO: add option to remove server from network

    Node& getServer(std::size_t idx);
    std::size_t serversCount() const;
};

