#include "foo.h"
#include <iostream>

using namespace std;



/*
	member initializer list: variable ( value )
	Class::Class(args) : arg1(val1), arg2(val2) { constructor }
*/

Foo::Foo(int a, int b)
: var(a), cvar(b)
{
	
}

void Foo::print()
{
	cout << "var is " << var <<endl;
	cout << "constant var is " << cvar <<endl;
}