#include "UdpClient.hpp"

int main(int argc, char* argv[]) {
    if(argc != 3) {
        Usage();
    }
    UdpClient cli(atoi(argv[2]), argv[1]);
    cli.Init();
    cli.Start();
    return 0;
}