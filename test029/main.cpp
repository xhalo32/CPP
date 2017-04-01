#include <iostream>
#include <cstdlib>

using namespace std;


class Foo
{
	int bar;

	public:
		Foo()
		{
			bar=10;
		}

		Foo(int a)
		{
			this->bar=a;
		}

		void print()
		{
			cout << bar << endl;
		}

		void * operator new(size_t size)
		{
			void * pointer;
			cout << "Size: " << size << endl;
			pointer = malloc(size);

			if (!pointer)
			{
				throw 1;
			}

			return pointer; // why?! It's a void function
		}

		void operator delete(void * pointer)
		{
			cout << "Deleted" << endl;
			free(pointer);
		}
};

// you cannot overload ? :: .* . operators
// new & delete operators can be overloaded

// new returns a pointer

int main()
{
	/*
	Foo * foop = new Foo;

	foop->print();

	Foo foo = * foop;
	foo.print();
	*/

	Foo * foop;
	try
	{
		foop = new Foo(20);
		foop->print();

		delete foop;

	}catch(int b)
	{
		cout << "Err: " << b << endl;
	}

	return 0;
}