#include <iostream>
#include "foo.cpp"

using namespace std;

int main()
{
	Foo foo_object(5, 10);
	foo_object.print();

	return 0;
}