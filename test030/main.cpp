#include <iostream>
#include <string>

using namespace std;



class Foo
{
	string foo;
	int bar;
	public:
		Foo()
		{
			foo = "bar";
			bar = 10;
		}

		friend ostream &operator << (ostream &output, Foo &f);
		friend istream &operator >> (istream &input, Foo &f);
};

ostream &operator << (ostream &output, Foo &f)
{
	output << "Watts up" << endl;
	output << "foo is " << f.foo << " and bar is " << f.bar << endl;
	return output;
}

istream &operator >> (istream &input, Foo &f)
{
	input >> f.foo >> f.bar;
	return input;
}


int main()
{
	cout << "Press buttons " << endl;
	Foo foo;
	cin >> foo;
	cout << foo;

	return 0;
}