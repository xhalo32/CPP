#include <iostream>
#include <string>
using namespace std;

#include "classes.h"



int main()
{
	Foo FooObject("What's Up");

	FooObject.Bar();

	FooObject.SetSentence("Dogs");
	
	FooObject.Bar();

	return 1;
}