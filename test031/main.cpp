#include <iostream>
#include <string>
using namespace std;

/*
class Foo
{
	public:
		string *name;
		int age;

		Foo(string a, int b)
		{
			name = new string(a);
			age = b;
		}

		void change(string a, int b)
		{
			// *(this->name) is not same as name

			*(this->name) = a;
			age = b;
		}

		void print()
		{
			cout << "Hi " << *name << " here. I am " << age << " years older than you!" << endl;
		}	
};



int main()
{
	Foo foo("Michael", 20);
	//creating a duplicate with all the same values and pointers!
	//therefore there are now same pointers in different objects
	Foo dupfoo = foo;

	foo.print();
	dupfoo.print();

	dupfoo.change("leahciM", 05);

	foo.print();
	dupfoo.print();

	return 0;
}
*/

class Foo
{
	public:
		string *name;
		int age;

		Foo(string a, int b)
		{
			name = new string(a);
			age = b;
		}

		void change(string a, int b)
		{
			// *(this->name) is not same as name

			*(this->name) = a;
			age = b;
		}

		// copy constructor
		// this way a new memory location is allocated for the 'new' object
		Foo(const Foo &f)
		{
			cout << "Copying..." << endl;
			name = new string( * f.name);
			age = f.age;
		}

		void print()
		{
			cout << "Hi " << *name << " here. I am " << age << " years older than you!" << endl;
		}	
};



int main()
{
	Foo foo("Michael", 20);
	//creating a duplicate with all the same values and pointers!
	//therefore there are now same pointers in different objects

	//with the copy contructor the name in object foo will be copied into another location
	
	Foo dupfoo = foo;

	foo.print();
	dupfoo.print();

	dupfoo.change("leahciM", 05);

	foo.print();
	dupfoo.print();

	return 0;
}