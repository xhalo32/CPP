#include <iostream>
using namespace std;

void print_array(int array[], int array_len);

int main()
{
	int foo[3] = {1, 2, 3};
	int bar[4] = {-1, -2, -3, -4};

	print_array(foo, 3);
	print_array(bar, 4);

}

void print_array(int array[], int array_len)
{
	for (int i = 0; i < array_len; ++i)
	{
		cout << array[i] << endl;
	}
}