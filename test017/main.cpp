#include <iostream>

using namespace std;


/*
class Foo
{
	public:
		void setfoo(int a){ foo = a; }

	protected:
		int foo;

};

class Bar : public Foo
{
	public:
		void print()
		{
			cout << "Whats up: " << foo << endl;
		}
};
class Barcycle : public Foo
{
	public:
		void print()
		{
			cout << "Not munch: " << foo << endl;
		}
};



int main()
{
	Bar bar;
	Barcycle bcycle;

	// Foo pointer made from an instance that derived from Foo
	// all Foo attributes are usable.
	// Using Foo's attributes still have effect on the derived class

	Foo * foo1 = &bar;
	Foo * foo2 = &bcycle;

	foo1->setfoo(9000);

	foo2->setfoo(9001);

	bar.print();
	bcycle.print();
}
*/


class Foo
{
	public:
		void setfoo(int a) {foo = a;}

		// Each derived class will have the 
		// attributes defined after the keyword 'virtual'
		virtual void print() {
			cout << "kekt " << foo << endl;
		}

		// An abstract class is a class with only pure virtual functions
		// A pure virtual function is required to be overridden
		virtual void noprint() = 0;

	protected:
		int foo;
};

class Bar : public Foo
{
	public:
		void print()
		{
			cout << "What's UP " << foo << endl;
		}
};
class Barcycle : public Foo
{	
	public:
		void print()
		{
			cout << "Not puNCh " << foo << endl;
		}
};
class Nobar : public Foo
{
	// We won's override the virtual function 
};


int main()
{
	Bar bar;
	Barcycle barcycle;
	Nobar nobar;

	Foo * foobar = &bar;
	Foo * foobarcycle = &barcycle;
	Foo * foonobar = &nobar;

	foobar->setfoo(9000);
	foobarcycle->setfoo(9001);


	foobar->print();
	foobarcycle->print();
	foonobar->print();
}