#include <iostream>
using namespace std;


template<class T, class U>

T leastOf(T a, U b)
{
	return (a < b ? a : b);
}



int main()
{
	int x = 3;
	double y = 2.543;

	
	cout << leastOf(x, y) << endl;
}