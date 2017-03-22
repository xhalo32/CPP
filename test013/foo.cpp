#include "foo.h"



Foo::Foo(int a)
: a(a)
{	
}

void Foo::print()
{
	cout << a << endl;

	// 'this' is a pointer meaning the current object: "foo"
	cout << this -> a << endl;

	// to use 'this' as anything but an address you use '*this'
	cout << (*this).a << endl;
}