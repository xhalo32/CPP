#include <iostream>
#include <SFML/Network.hpp>


const unsigned short port=50001;

int main()
{
	// server socket
	sf::TcpListener listener;
	// open port
	if (listener.listen(port) != sf::Socket::Done) return 1;
    std::cout<<"Server listening port "<<port<<std::endl;
	// wait for connection
	sf::TcpSocket socket;
	if (listener.accept(socket) != sf::Socket::Done) return 1;
	
	// send a message to the client
	const char out[]="Hello";
	if (socket.send(out,sizeof(out)) != sf::Socket::Done) return 1;
	std::cout<<"Packet send"<<std::endl;
	// recieve message from the client
	char in[128];
	std::size_t received;
	if (socket.receive(in, sizeof(in), received) != sf::Socket::Done) return 1;
	std::cout<<"Received: "<<in<<std::endl;

	std::cout<<"Press enter to exit..."<<std::endl;
	std::cin.ignore(10000, '\n');

	return 0;
}
