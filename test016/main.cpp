#include <iostream>
using namespace std;

class Foo
{
	// public variables can be accessed by anyone anywhere
	// in the program
	public:
		int pubvar;

	// protected variables can be accessed 
	// by friends and derived classes
	protected:
		int provar;

	// private variables can be accessed only by the base class
	private:
		int privar;
};

class Bar: public Foo
{
	public:
		void print()
		{
			pubvar = 10;
			cout << pubvar << endl;

			provar = 20;
			cout << provar << endl;

			privar = 25;
			cout << privar << endl;
			// throws an error
		}

};



int main()
{
	Bar bar;
	bar.print();



	return 9000;
}