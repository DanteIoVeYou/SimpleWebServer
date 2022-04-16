#include "UdpServer.hpp"

int main(int argc, char* argv[])
{
    if(argc != 2) {
        Usage();
    }
    UdpServer srv(atoi(argv[1]));
    srv.Init();
    srv.Start();
    return 0;
}