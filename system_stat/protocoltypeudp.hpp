#ifndef PROTOCOLTYPEUDP_H
#define PROTOCOLTYPEUDP_H

#include "protocoltype.hpp"

class ProtocolTypeUDP : public ProtocolType
{
public:
    ProtocolTypeUDP(int port);

    virtual void listen();
    virtual void init();
    virtual int sendData(int fd, const std::__cxx11::string& data);
    virtual int readData(int fd, std::__cxx11::string& str);
};

#endif // PROTOCOLTYPEUDP_H
