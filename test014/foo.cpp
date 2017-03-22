#include "foo.h"



Foo::Foo()
{
	
}

Foo::Foo(int a)
{
	num = a;
}

Foo Foo::operator+(Foo fobj)
{
	Foo newfoo;
	newfoo.num = num + fobj.num;

	return(newfoo);
}