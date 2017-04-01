#include <iostream>

using namespace std;


class Foo
{
	int bar;
	public:
		Foo(int a)
		{
			bar = a;
		}

		void print()
		{
			cout << bar << endl;
		}

		Foo * operator->()
		{
			return this;
		}
};


int main()
{
	Foo foo(27);

	foo.print();
	foo->print();

	return 0;
}