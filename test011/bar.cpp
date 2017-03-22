#include "bar.h"

using namespace std;


// using 		name does not confuse the program
Bar::Bar(string name, Foo bday)
: name(name), date_birth(bday)
{
	
}

void Bar::print()
{
	cout << "Name: " << name << endl;

	date_birth.print_date();
}