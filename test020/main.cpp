#include <iostream>
using namespace std;


template <class T>
class Foo
{
	T a, b;	
	public:
		Foo(T n1, T n2)
		{
			a = n1; b = n2;
		}
		T greater();
};

template <class T>
T Foo<T>::greater()
{
	return (a > b ? a : b);
}


int main()
{
	// <int> meant substitute every T with int
	Foo <int> foo(100, 20);

	cout << foo.greater() << endl;
}