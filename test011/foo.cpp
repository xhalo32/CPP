#include "foo.h"

using namespace std;



Foo::Foo(int y, int m, int d)
{
	year = y;
	month = m;
	day = d;
}

void Foo::print_date()
{
	cout << "Year: " << year << endl;
	cout << "Month: " << month << endl;
	cout << "Day: " << day << endl;
}