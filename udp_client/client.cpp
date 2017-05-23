#include "client.h"

Client::Client(std::__cxx11::string server, int port) : SERVER(server), PORT(port)
{
    clear_buffer();
    init();
}

void Client::init()
{
    slen = sizeof(si_other);

    // get file descriptor
    if (-1 == (sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)))
    {
        std::cerr << "Error: socket()" << std:: endl;
        exit(1);
    }


    // clear memory
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);


    if (0 == inet_pton(si_other.sin_family, SERVER.c_str(), &si_other.sin_addr))
    {
        std::cerr << "Error: inet_pton()" << std:: endl;
        close(sock_fd);
        exit(1);
    }


    // three testing messages.. nothing special..
    for (int i = 0; i < 3; ++i)
    {
        printf("Enter message : ");
        std::cin >> buff; // read message to first space

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


        // clear the buffer
        clear_buffer();


        // set poll struct.. timeout 2 seconds
        pfd.fd = sock_fd;
        pfd.events = POLLIN;

        pfd_rv = poll(&pfd, 1, 2000);
        if (pfd_rv == -1)
        {
            // TODO: poll return error
            exit(1);
        }
        else if (pfd_rv == 0)
        {
            strcpy(buff, "Timeout! No data in 2 seconds!\n\0");
        }
        else
        {
            int received = recvfrom(sock_fd, buff, BUFF_SIZE, 0, (struct sockaddr *) &si_other, &slen);
            if (received == -1)
            {
                // TODO: error in recvfrom()
                exit(1);
            }
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
