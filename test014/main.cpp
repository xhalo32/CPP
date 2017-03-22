#include <iostream>
using namespace std;

#include "foo.cpp"



int main()
{
	Foo a(2);
	Foo b(5);
	Foo c;

	c = a + b;

	cout << c.num << endl;

	cout << (a + b + b).num << endl;

	return 1;
}