#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <pthread.h>

namespace Server
{
	using namespace std;
	void Usage(std::string proc) {
		printf("Usage:\n\t%s [port]\n", proc.c_str());
	}
	class TcpServer
	{
	public:
		TcpServer(uint16_t port = 8080): _port(port), _listen_sock(-1) {}
		~TcpServer() {
			close(_listen_sock);
		}
		static void* handler(void* args) {
			pthread_detach(pthread_self());
			int sock = *(int*)args;
			delete (int*)args;
			while(true) {
				char buffer[1024] = {0};
				ssize_t s = recv(sock, buffer, sizeof(buffer) - 1, 0);
				if(s > 0) {
					// receive success
					buffer[s] = 0;
					std::string msg = buffer;
					std::cout << msg << std::endl;
					if(msg == "quit") {
						std::cout << "quit..." << std::endl;
						break;
					}
					ssize_t sendret = send(sock, buffer, strlen(buffer), 0);
					if(sendret < 0) {
						std:cerr << "Send Failed" << std::endl;
						continue;
					}
				}
				else if(s == 0) {
					// quit
					std::cout << "quit..." << std::endl;
					break;
				}
				else {
					// receive Fail
					std::cerr << "Receive Failed." << std::endl;
					continue;
				}
			}
			close(sock);
		}
		void Init() {
			// 1. create socket
			_listen_sock = socket(AF_INET, SOCK_STREAM , 0);
			if(_listen_sock < 0) {
				std::cerr << "Create Sock Failed." << std::endl;
				exit(1);
			}
			// 2. bind socket
			sockaddr_in local;
			memset(&local, 0, sizeof(local));
			local.sin_family = AF_INET;
			local.sin_port = htons(_port);
			local.sin_addr.s_addr = INADDR_ANY;
			if(bind(_listen_sock, (sockaddr*)&local, sizeof(local)) < 0) {
				std::cerr << "Bind Failed." << std::endl;
				exit(2);
			}
			// 3. listen
			if(listen(_listen_sock, 5) < 0) {
				std::cerr << "Listen Failed." << std::endl;
				exit(3);
			}

		}
		void Start() {
			for(;;) {
				sockaddr_in peer;
				socklen_t len = sizeof(peer);
				memset(&peer, 0, sizeof(peer));
				int sock = accept(_listen_sock, (sockaddr*)&peer, &len);
				if(sock < 0) {
					std::cerr << "Accept Failed" << std::endl;
					exit(4);
				}
				// print client ip and port
				uint16_t port = htons(peer.sin_port);
				std::string ip = inet_ntoa(peer.sin_addr);
				std::cout << "[" << ip << "][" << port << "] login..." << std::endl;
				// create new thread to deal with sock
				pthread_t tid;
				int* psock = new int(sock);
				pthread_create(&tid, nullptr, handler, psock);
			}
		}
	private:
		uint16_t _port;
		int _listen_sock;
	};
} // namespace end
