#include <iostream>
#include <SFML/Network.hpp>

const unsigned short port=50001;

int main()
{
	sf::IpAddress server;
	do
	{
		std::cout<<"Type in the address of the server: ";
		std::cin>>server;
	}
	while (server==sf::IpAddress::None);

	// create socket for communication
	sf::TcpSocket socket;
	// connect to the server
	if (socket.connect(server, port) != sf::Socket::Done) return 1;
	std::cout<<"Connection esablished to "<<server<<std::endl;

	char in[128];
    std::size_t received;
    if (socket.receive(in, sizeof(in), received) != sf::Socket::Done) return 1;
    std::cout<<"Message received from the server: "<<in<<std::endl;

	// send message
	const char out[]="Hi";
    if (socket.send(out, sizeof(out)) != sf::Socket::Done) return 1;
    std::cout<<"Message sent to the server"<<std::endl;

	std::cout<<"Press enter to exit"<<std::endl;
	std::cin.ignore(10000, '\n');

	return 0;
}
