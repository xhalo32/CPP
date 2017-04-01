#include <iostream>
#include <string>

using namespace std;



int main()
{
	string s;
	getline(cin, s);
	cout << s.substr(7, 8) << endl;

	cout << s.find('a') << endl;

	cout << s.replace(9, 4, "REPLACED") << endl;

	cout << s.insert(9, "Insert ") << endl;

	cout << s.erase(20) << endl;

	string a = "apples";
	string b = "pears";

	cout << a << b << endl;

	a.swap(b);

	cout << a << b << endl;
}