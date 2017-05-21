#pragma once

#include <memory>
#include <deque>
#include <future>

#include "node.hpp"
#include "protocoltype.hpp"
#include "protocoltypetcp.hpp"
#include "protocoltypeudp.hpp"
#include "network.hpp"


class Client
{
private:
    std::shared_ptr<ProtocolType> protocol;
    const Network* network;

    std::__cxx11::string report;

    void init();
    bool retrieveData();
    std::shared_ptr<Client> createObject();

public:
    explicit Client(std::shared_ptr<ProtocolType> protocol, const Network* network);


    const std::__cxx11::string& getReport() const;
    void setServer(const Node&);
    void collectAllReports();
};
