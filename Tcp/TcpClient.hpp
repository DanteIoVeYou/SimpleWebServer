#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <cstdlib>

// namespace Client
// {
    void Usage(std::string proc) {
        printf("Usage:\n\t%s [ip] [port]\n", proc.c_str());
    }
    class TcpClient {
    public:
        TcpClient(uint16_t port, std::string ip): _port(port), _ip(ip) {}
        ~TcpClient(){
            close(_sock);
        }
        void Init() {
            _sock = socket(AF_INET, SOCK_STREAM, 0);
            if(_sock < 0) {
                std::cout << "create socket failed." << std::endl;
                exit(1);
            }
            sockaddr_in peer;
            memset(&peer, 0, sizeof(peer));
            peer.sin_family = AF_INET;
            peer.sin_port = htons(_port);
            peer.sin_addr.s_addr = inet_addr(_ip.c_str());
            if(connect(_sock, (sockaddr*)&peer, sizeof(peer)) < 0) {
                std::cerr << "connect failed." << std::endl;
                exit(2);
            }
            // connect success
        }
        void Start() {
            while(true) {
                char buffer[1024] = {0};
                std::cout << "enter# ";
                fflush(stdout);
                read(0, buffer, sizeof(buffer)-1);
                // std::string buffer;
                // std::getline(std::cin, buffer);
                // ssize_t s = send(_sock, buffer.c_str(), strlen(buffer.c_str()), 0);
                ssize_t s = send(_sock, buffer, strlen(buffer) - 1, 0);
                if(s < 0) {
                    std::cerr << "send failed" << std::endl;
                    continue;
                }
                else {
                    // send success
                    std::string message(buffer, 4);
                    if(message == "quit") {
                        break;
                    }
                    buffer[0] = 0;
                    ssize_t s = recv(_sock, buffer, sizeof(buffer), 0);
                    if(s < 0) {
                        std::cerr << "recv failed" << std::endl;
                        continue;
                    }
                    else {
                        // recv success
                        buffer[s] = 0;
                        std::cout << "echo: " << buffer << std::endl;
                    }
                }
            }
        }
    private:
        uint16_t _port;
        std::string _ip;
        int _sock;
    };
// }// namespace end
