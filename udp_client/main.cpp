
#include <client.h>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Too few arguments! Usage: {app_name} {server_ip_to_connect} {port}\n");
        exit(1);
    }

    std::string server = argv[1];
    int port = atoi(argv[2]);

    Client cl(server, port);

    return 0;
}
