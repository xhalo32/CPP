#include <iostream>

using namespace std;


class Foo
{
	int subjects[3];
	public:
		Foo(int a, int b, int c)
		{
			subjects[0] = a;
			subjects[1] = b;
			subjects[2] = c;
		}
		int operator[](int i)
		{
			return subjects[i];
		}
	
};

int main()
{
	Foo foo(10, 20, 30);
	cout << foo[0] << endl;


	return 0;
}