#include <iostream>

using namespace std;



int main()
{
	try
	{
		int num1;
		cout << "Num 1: " << endl;
		cin >> num1;

		int num2;
		cout << "Num 2: " << endl;
		cin >> num2;

		if (num2 == 0) throw 0;

		cout << (float) num1 / (float) num2 << endl;

	}catch(...)
	{
		cout << "Err" << endl;
	}
}