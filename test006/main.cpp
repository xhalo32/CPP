#include <iostream>

using namespace std;



int main()
{
	int a[5];

	int * p0, p1;


	p0 = &a[0];
	p1 = &a[1];


	cout << p0 << endl;
	cout << p1 << endl;
}