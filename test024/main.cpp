#include <iostream>
#include <fstream>

using namespace std;



int main()
{
	ofstream file;
	file.open("data");

	file << "Hello\n";

	file.close();

}