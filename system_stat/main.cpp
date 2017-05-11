
#include "server.hpp"
#include "client.hpp"
#include "reporter.hpp"
#include "dispatcher.hpp"
#include "network.hpp"

#include "protocol_types.hpp"

const std::size_t DEFAULT_PORT = 13651;

int main(int argc, char *argv[])
{
    std::size_t port = DEFAULT_PORT;
    if (argc > 1)
    {
        port = std::atoi(argv[1]);
    }

    Server srv (port, ProtocolType::UDP);
    Client cln;
    Reporter rpt;
    Network ntw;

    Dispatcher disp (&srv, &cln, &rpt, &ntw);
    disp.run();

	return 0;
}

