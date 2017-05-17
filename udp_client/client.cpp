#include "client.h"

Client::Client(std::__cxx11::string server, int port) : SERVER(server), PORT(port)
{
    clear_buffer();
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

    /*if (0 == inet_pton(si_other.sin_family, SERVER.c_str(), &(si_other.sin_addr)))
    {
        std::cerr << "Error: inet_pton()" << std:: endl;
        close(sock_fd);
        exit(1);
    }*/


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
        const int buff_len = strlen (buff);
        const int send_data = sendto(sock_fd, buff, buff_len, 0 , (struct sockaddr *) &si_other, slen);

        if (-1 == send_data)
        {
            std::cerr << "Error: sendto()" << std:: endl;
            close(sock_fd);
            exit(1);
        }
        else if (buff_len != send_data)
        {
            std::cerr << "Warning: --buff_len: " << buff_len << " --send_data: " << send_data << std:: endl;
        }

        // clear the buffer by filling null, it might have previously received data
        clear_buffer();

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

void Client::clear_buffer()
{
    memset(buff,'\0', BUFF_SIZE);
}
