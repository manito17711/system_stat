#ifndef PROTOCOLTYPETCP_H
#define PROTOCOLTYPETCP_H

#include <protocoltype.hpp>

class ProtocolTypeTCP : public ProtocolType
{
public:
    ProtocolTypeTCP(int port);

    virtual void listen();
    virtual void init();
};

#endif // PROTOCOLTYPETCP_H
