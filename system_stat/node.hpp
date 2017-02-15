#pragma once

#include <string>

struct Node
{
    std::__cxx11::string ipAddr;
    std::size_t port;

    explicit Node(std::__cxx11::string ipAddr, std::size_t port);
};

