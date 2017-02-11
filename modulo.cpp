#include <iostream>

using namespace std;


int mod(int x, int y)
{
	if(x < y) return x;
	return mod(x - y, y);
}

int main(int argc, char * argv[])
{
	int x = atoll(argv[1]);
	int y = atoll(argv[2]);

	cout << mod(x, y) << endl;

	return 0;
}