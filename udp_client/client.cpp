#include "client.h"

Client::Client(std::__cxx11::string server, int port) : SERVER(server), PORT(port)
{
    memset(buff,'\0', BUFF_SIZE);
    init();
}

void Client::init()
{
    slen = sizeof(si_other);

    if (-1 == (sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)))
    {
        std::cerr << "Error: socket()" << std:: endl;
        exit(1);
    }

    // set connection non-blocking
    fcntl(sock_fd, F_SETFL, O_NONBLOCK);

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    if (0 == inet_aton(SERVER.c_str(), &si_other.sin_addr))
    {
        std::cerr << "Error: inet_aton()" << std:: endl;
        exit(1);
    }

    // three testing messages.. nothing special..
    for (int i = 0; i < 3; ++i)
    {
        printf("Enter message : ");
        std::cin >> buff;

        //send the message
        if (-1 == sendto(sock_fd, buff, strlen(buff), 0 , (struct sockaddr *) &si_other, slen))
        {
            std::cerr << "Error: sendto()" << std:: endl;
            exit(1);
        }

        // clear the buffer by filling null, it might have previously received data
        memset(buff,'\0', BUFF_SIZE);

        // sleep for two seconds..
        sleep(2);

        // try to receive some data
        if (-1 == recvfrom(sock_fd, buff, BUFF_SIZE, 0, (struct sockaddr *) &si_other, &slen))
        {
            strcpy(buff, "recvfrom() failed or server does not respond in 2 seconds!\n\0");
        }

        std::cout << buff << std::endl;
    }

    close (sock_fd);
    sock_fd = -1; // set invalid data to file descriptor
}
