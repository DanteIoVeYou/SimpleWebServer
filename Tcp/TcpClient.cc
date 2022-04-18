#include "TcpClient.hpp"
int main(int argc, char* argv[])
{
    if(argc != 3) {
        Usage(argv[0]);
        return 1;
    }
    // Client::TcpClient cli = new Client::TcpClient(atoi(argv[2]), agrv[1]);
    TcpClient* cli = new TcpClient(atoi(argv[2]), argv[1]);
    cli->Init();
    cli->Start();
    return 0;
}
