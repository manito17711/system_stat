#ifndef PROTOCOLTYPEUDP_H
#define PROTOCOLTYPEUDP_H

#include "protocoltype.hpp"

class ProtocolTypeUDP : public ProtocolType
{
public:
    ProtocolTypeUDP(int port);

    virtual void listen();
    virtual void initSocketDescriptor();
};

#endif // PROTOCOLTYPEUDP_H
