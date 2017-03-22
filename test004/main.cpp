#include <iostream>
using namespace std;


void passByVal(int x);
void passByRef(int * x);

int main()
{
	int a = 10;
	int b = 12;

	passByVal(a);
	passByRef(&b);

	cout << a << endl;
	cout << b << endl;

	cout << endl;
	
	cout << &a << endl;
	cout << &b << endl;

	cout << endl;
	cout << *(&a+1) << endl; // location of a + 1 = b

	// & means get location of variable 
	// * means return value from location
}

void passByVal(int x)
{
	x = 100;
}

void passByRef(int * x)
{
	*x = 50;
}