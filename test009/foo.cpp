#include <iostream>

#include "foo.h"

using namespace std;

void Foo::do1()
{
	cout << "Doing 1..." << endl;
}

// constant function
void Foo::do2() const
{
	cout << "Doing 2 constantly..." << endl;
}