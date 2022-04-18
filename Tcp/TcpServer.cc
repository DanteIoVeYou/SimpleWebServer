#include "TcpServer.hpp"

int main(int argc, char* argv[])
{
    if(argc != 2) {
        // Server::Usage(argv[0]);
        Usage(argv[0]);
        return 1;
    }
    TcpServer* srv = new TcpServer(atoi(argv[1]));
    // Server::TcpServer* srv = new Server::TcpServer(atoi(argv[1]));
    srv->Init();
    srv->Start();
    return 0;
}
