
#include "server.hpp"
#include "client.hpp"
#include "reporter.hpp"
#include "dispatcher.hpp"
#include "network.hpp"

#include "protocoltype.hpp"
#include "protocoltypetcp.hpp"
#include "protocoltypeudp.hpp"

#include <memory>

const std::size_t DEFAULT_PORT = 13651;

int main(int argc, char *argv[])
{
    std::size_t port = DEFAULT_PORT;
    if (argc > 1)
    {
        port = std::atoi(argv[1]);
    }


    //Server<ProtocolTypeUDP> srv;
    //Client<ProtocolTypeUDP> cln;

    Network ntw;
    Reporter rpt;

    std::shared_ptr<ProtocolType> protocol_srv (new ProtocolTypeUDP(port));
    Server srv (protocol_srv);

    std::shared_ptr<ProtocolType> protocol_cln (new ProtocolTypeUDP(port));
    Client cln (protocol_cln, &ntw);

    Dispatcher disp (&srv, &cln, &rpt, &ntw);
    disp.run();

	return 0;
}

