#include "server.h"
#include "client.h"

#include <iostream>

using namespace std;

int main()
{
	char sel;
	cout<<"Client(c) or Server(s): ";
	cin>>sel;
	cout<<endl;

	int rval=0;
	if (sel=='c')
	{
		char address[24];
		unsigned short port;
		cout<<"Enter address of server: ";
		cin>>address;
		cout<<"Enter port of server: ";
		cin>>port;
		
		rval=connectToServer(address,port);
	}
	else if (sel=='s')
	{
		unsigned short port;
		char name[24];
		cout<<"Enter port: ";
		cin>>port;
		cout<<"Enter name of server: ";
		cin>>name;
		
		rval=hostServer(port,name);
	}
	switch(rval)
	{
		case 1: cout<<"Connection failed"<<endl; break;
		case 2: cout<<"Disconnected"<<endl; break;
	}
	return 0;
}
