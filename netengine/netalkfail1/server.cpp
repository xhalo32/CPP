#include <SFML/Network.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace sf;



int hostServer(unsigned short port=50001, char *name=(char*)"Netalk!")
{
	TcpListener listener;
	// open port
	Socket::Status stat=listener.listen(port);
	while (stat==Socket::NotReady) {}
    cout<<"Server listening on port "<<port<<endl;
	// wait for connection
	TcpSocket socket;
	while (listener.accept(socket)==Socket::NotReady) {}
	cout<<"Client connected!"<<endl;

	if (socket.send(name,sizeof(name)) != Socket::Done) return 2;
    
	// send a custom message to the client
	while (1)
	{
		cout<<name<<"-Server: ";
		char out[33]="";
		cin.getline(out,sizeof(out));
		if (strlen(out)!=0)
			if (socket.send(out,sizeof(out)) != Socket::Done) return 2;

		// recieve message from the client
        char in[33];
        size_t received;
		Socket::Status rec;
		rec=socket.receive(in, sizeof(in), received);
		if (rec==Socket::Done)
			cout<<name<<"-Client: "<<in<<endl;
	}
}
