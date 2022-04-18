all:TcpServer TcpClient
TcpSerever: TcpServer.cc
	g++ -o $@ $^ -std=c++11 -lpthread
TcpClient: TcpClient.cc
	g++ -o $@ $^ -std=c++11
.PHONY:clean
clean:
	rm -f TcpSercer TcpClient
