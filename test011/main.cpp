#include <iostream>
#include <string>

#include "foo.cpp"
#include "bar.cpp"

using namespace std;

int main()
{
	Bar man("Pete", Foo(1900, 12, 31));

	man.print();

	return 1;
}