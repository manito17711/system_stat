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


int ProtocolTypeTCP::readData(int fd, std::__cxx11::string &str)
{
    return -1;
}
