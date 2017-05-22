#ifndef PROTOCOLTYPEUDP_H
#define PROTOCOLTYPEUDP_H

#include "protocoltype.hpp"

class ProtocolTypeUDP : public ProtocolType
{
public:
    ProtocolTypeUDP(int port);

    virtual void startListen();
    virtual void initSocket();
    virtual int sendData(int fd, const std::__cxx11::string& data);
    virtual int readData(int fd, std::__cxx11::string& str);
    virtual std::shared_ptr<ProtocolType> createObject();
};

#endif // PROTOCOLTYPEUDP_H
