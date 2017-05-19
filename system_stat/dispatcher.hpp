#pragma once

#include <memory>
#include <future>

#include "server.hpp"
#include "client.hpp"
#include "reporter.hpp"
#include "network.hpp"
#include "connection_types.hpp"

class Dispatcher
{
private:
	Server *server;
    Client *client;
    Reporter *reporter;
    Network *network;

    void onConnection(int fd, ConnType type);

public:
    explicit Dispatcher(Server *srv, Client *cln, Reporter *rpt, Network *network);
	
    void run();
};
