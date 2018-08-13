#include <SFML/Network.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace sf;

int connectToServer(char * ser, unsigned short port=50001){
	
	IpAddress server = ser;
	
	if (server==IpAddress::None) return 1;
	
	// create socket for communication
	TcpSocket socket;
	
	// connect to the server
	if (socket.connect(server, port) != Socket::Done) {
		cout << "Couldn't connect..." << endl;
		return 1;
		}
	cout<<"Connection esablished to "<<server<<endl;
	
	char name[24];
	size_t received;
	if (socket.receive(name, sizeof(name), received) != Socket::Done) return 2;
	
	while(1){
		
		char in[33];
		size_t received;
		Socket::Status rec;
		rec = socket.receive(in, sizeof(in), received);
		if(rec == Socket::Done) cout<<name<<"-Server: "<<in<<endl;
		
		// send message
		cout << name << "-Client: ";
		char out[33] = "";
		cin.getline(out, sizeof(out));
		if(strlen(out) == 0){
			if (socket.send(out, sizeof(out)) != Socket::Done) return 2;
		}
		
	}

	return 0;
	
}