#include <iostream>

using namespace std;

/*
A class can have friends that are prototyped in the class as a friend.
*/

class Foo
{
	public:
		Foo()
		{
			bar=0;
		};
	private:
		int bar;

	friend void FoosFriend(Foo &fobj);
};

void FoosFriend(Foo &fobj)
{
	fobj.bar = 9000;
	cout << fobj.bar << endl;
}


int main()
{
	Foo bob;

	FoosFriend(bob);
}