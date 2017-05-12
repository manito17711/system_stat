#ifndef PROTOCOLTYPETCP_H
#define PROTOCOLTYPETCP_H

#include <protocoltype.hpp>

class ProtocolTypeTCP : public ProtocolType
{
public:
    ProtocolTypeTCP(int port);

    virtual void run();
    virtual void initSocketDescriptor();
};

#endif // PROTOCOLTYPETCP_H
