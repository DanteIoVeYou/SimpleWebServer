#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>

void Usage() {
    printf("usage:\n\t./UdpClient [ip] [port]\n");
}
class UdpClient
{
public:
    UdpClient(uint16_t port, std::string ip): _port(port), _ip(ip), _sock(-1) {}  
    ~UdpClient() {
        close(_sock);
    }
    void Init() {
        // Create Socket fd
        _sock = socket(AF_INET, SOCK_DGRAM, 0);
        if(_sock < 0) {
            std::cerr << "Create Socket Failed" << std::endl;
            exit(1);
        }
    }
    void Start() {
        struct sockaddr_in peer;
        memset(&peer, 0, sizeof(peer));
        peer.sin_port = htons(_port);
        peer.sin_addr.s_addr = inet_addr(_ip.c_str());
        peer.sin_family = AF_INET;
        for(;;) {
            // Send msg to Server
            std::string msg;
            std::cout << "Input>";
            fflush(stdout);
            std::getline(std::cin, msg);
            ssize_t s1 = sendto(_sock, msg.c_str(), strlen(msg.c_str()), 0, (struct sockaddr*)&peer, sizeof(peer));
            std::cout << s1 << std::endl;
            if(s1 < 0) {
                std::cerr << "Send Failed" << std::endl;
                exit(2);
            }
            // Receive Data
            char buffer[256] = {0};
            ssize_t s = recvfrom(_sock, buffer, sizeof(buffer) - 1, 0, nullptr, nullptr);
            if(s < 0) {
                std::cerr << "Reveive Data Failed" << std::endl;
                exit(3);
            }
            buffer[s] = 0;
            std::cout << buffer << std::endl;
        }
    }        
private:
   uint16_t _port;
   std::string _ip; 
   int _sock;
};
