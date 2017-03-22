#include <iostream>
using namespace std;

#include "foo.h"



int main()
{
	Foo foo_object;				// create an object
	Foo * foop = &foo_object;	// create a pointer to that object
	

	foo_object.tellFoo();		// call a method from the object
	foop -> tellFoo();			
	// use the arrow member selection operator
	// to call the method from the object under the pointer

	return 0;
}