
#include "server.hpp"
#include "client.hpp"
#include "reporter.hpp"
#include "dispatcher.hpp"
#include "network.hpp"

#include "protocoltype.hpp"
#include "protocoltypetcp.hpp"
#include "protocoltypeudp.hpp"

#include <memory>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

const std::size_t DEFAULT_PORT = 13651;

void sigchld_handler(int)
{
    int saved_errno = errno;
    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}



int main(int argc, char *argv[])
{
    std::size_t port = DEFAULT_PORT;
    if (argc > 1)
    {
        port = std::atoi(argv[1]);
    }

    struct sigaction sa;
    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    // TODO:
    // Server<ProtocolTypeUDP> srv;
    // Client<ProtocolTypeUDP> cln;

    Network ntw;
    Reporter rpt;

    std::shared_ptr<ProtocolType> protocol_srv (new ProtocolTypeTCP(port));
    Server srv (protocol_srv);

    std::shared_ptr<ProtocolType> protocol_cln (new ProtocolTypeTCP(port));
    Client cln (protocol_cln, &ntw);

    Dispatcher disp (&srv, &cln, &rpt, &ntw);
    disp.run();

	return 0;
}

