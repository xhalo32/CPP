#include <iostream>

#include "foo.cpp"
#include "foo.h"

using namespace std;



int main()
{
	Foo fooo;
	fooo.do1();

	const Foo cfooo;
	cfooo.do2();

	return 0;
}