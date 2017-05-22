#ifndef PROTOCOLTYPETCP_H
#define PROTOCOLTYPETCP_H

#include "protocoltype.hpp"

class ProtocolTypeTCP : public ProtocolType
{
public:
    ProtocolTypeTCP(int port);

    virtual void startListen();
    virtual void initSocket();
    virtual int sendData(int fd, const std::__cxx11::string& data);
    virtual int readData(int fd, std::__cxx11::string& str);
    virtual std::shared_ptr<ProtocolType> createObject();

private:
    bool favicon(const char* req);
};

#endif // PROTOCOLTYPETCP_H
