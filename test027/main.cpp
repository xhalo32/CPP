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

		void operator()(int x)
		{
			bar = x;
		}
};


int main()
{
	Foo foo(27);
	foo.print();

	foo(270);
	foo.print();
}