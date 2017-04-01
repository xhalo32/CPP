#include <iostream>

using namespace std;


template <class number>
// Using templates you can work with multiple types

number sum(number a, number b)
{
	return a + b;
}



int main()
{
	double x = 1.5, y = 2;
	int x2 = 1.5, y2 = 2;

	cout << sum(x, y) << endl;
	cout << sum(x2, y2) << endl;

	return 0;
}