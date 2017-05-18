#ifndef PROTOCOLTYPETCP_H
#define PROTOCOLTYPETCP_H

#include <protocoltype.hpp>

class ProtocolTypeTCP : public ProtocolType
{
public:
    ProtocolTypeTCP(int port);

    virtual void listen();
    virtual void init();
    virtual int sendData(int fd, const std::__cxx11::string& data);
    virtual int readData(int fd, std::__cxx11::string& str);
};

#endif // PROTOCOLTYPETCP_H
