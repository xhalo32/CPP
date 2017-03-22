#include <iostream>

#include "Foo.h"

using namespace std;


// contructors and deconstructors do not have return values
Foo::Foo()
{
	cout << "Constructing..." << endl;
}

Foo::~Foo()
{
	cout << "Deconstructing..." << endl;
}