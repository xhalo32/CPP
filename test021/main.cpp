#include <iostream>
using namespace std;


template <class T>
class Foo
{
	public:
		Foo(T x)
		{
			cout << x << " is nto a charactier" << endl;
		}
};

template<>
class Foo<char>
{
	public:
		Foo(char x)
		{
			cout << x << " is a charawcteer" << endl;
		}	
};



int main()
{
	Foo <int> foo(120);
	Foo <char> fooc('a');



}