#include <iostream>
using namespace std;

#include "parent.cpp"
#include "child.cpp"



int main()
{
	Parent par;
	par.print();

	Child bob;
	bob.print();

	return 0;
}