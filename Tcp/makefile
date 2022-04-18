.PHONY:all
all:TcpServer TcpClient
TcpServer:TcpServer.cc
	g++ -o $@ $^ -std=c++11 -lpthread 
TcpClient:TcpClient.cc
	g++ -o $@ $^ -std=c++11 -lpthread 
.PHONY:clean
clean:
	rm -f TcpServer TcpClient
