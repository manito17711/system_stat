#ifndef PROTOCOLIMPL_H
#define PROTOCOLIMPL_H


class ProtocolImpl
{
public:
    ProtocolImpl();
    virtual ~ProtocolImpl();

private:
    int socket_fd;

};

#endif // PROTOCOLIMPL_H
