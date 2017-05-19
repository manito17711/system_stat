#include "protocoltypetcp.hpp"

ProtocolTypeTCP::ProtocolTypeTCP(int port) : ProtocolType(port)
{

}


void ProtocolTypeTCP::listen()
{

}


void ProtocolTypeTCP::init()
{

}


int ProtocolTypeTCP::sendData(int fd, const std::__cxx11::string &data)
{
    return -1;
}

int ProtocolTypeTCP::sendData(int fd, const std::__cxx11::string &data, sockaddr_in server)
{
    return -1;
}


int ProtocolTypeTCP::readData(int fd, std::__cxx11::string &str)
{
    return -1;
}

std::shared_ptr<ProtocolType> ProtocolTypeTCP::createObject()
{
    std::shared_ptr<ProtocolType> newObj (new ProtocolTypeTCP(port));
    return newObj;
}
