#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


class UdpServer {
public:
    UdpServer(uint16_t port = 8080): _port(port), _sock(-1) {
        
    }
    ~UdpServer() {
        
    }
    void Init() {
        // Create Socket fd
        _sock = socket(AF_INET, SOCK_DGRAM, 0);
        if(_sock < 0) {
            std::cerr << "create socket fails" << std::endl;
            exit(1);
        }
        // Bind Socket
        sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_port = _port;
        local.sin_family = AF_INET;
        local.sin_addr.s_addr = INADDR_ANY;
        if(bind(_sock,(sockaddr*) &local, sizeof(local)) < 0) {
            std::cerr << "Bind failed" <<std::endl;
            exit(2);
        }
    }
    void Start() {
        for(;;) {
            char buffer[256] = {0};
            // Receive Data From Socket
            ssize_t s = recv(_sock, buffer, sizeof(buffer), 0);
            if(s < 0) {
                std::cerr << "Recv Failed" << std::endl;
                exit(3);
            }
            // Print Data From Socket
            buffer[s] = 0;
            std::cout << buffer << endl;
            // Send Data Back to Client
            sockaddr_in peer;
            memset(&peer, 0, sizeof(peer));
            ssize_t s2 = sendto(_sock, buffer, sizeof(buffer), 0, (sockaddr*)peer, sizeof(peer));
            if(s2 < 0) {
                std::cerr << "Send Data Failed" << std::endl;
                exit(4);
            }

        }


    }
private:
    uint16_t _port;
    int _sock;
};