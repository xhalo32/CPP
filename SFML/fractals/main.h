#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

struct FractalPoint
{
	float x, y, side;
	int value;
	FractalPoint(float _x,float _y,float _side,int _value) :
		x(_x),y(_y),side(_side),value(_value) {}
	FractalPoint()
	{
		x=0;y=0;side=0;value=0;
	}
};

template <class T>
struct CircularBuffer
{
	size_t size;
	int pointer=0;
	T * nullvalue;
	T * bufferlist;
	CircularBuffer(size_t _size,T * _nullvalue) :
		size(_size),nullvalue(_nullvalue)
	{
		bufferlist=new T[size];
		for (int i=0;i<size;++i) bufferlist[i]=*nullvalue;
	}
	int push(T _element)
	{
		bufferlist[pointer]=_element;
		++pointer;
		pointer%=size;
		return pointer;
	}
	T operator[](size_t n) { return bufferlist[n]; }
}; 

template <class T>
struct FixedCircularBuffer
{
	size_t size;
	size_t fixed_size;
	int pointer=0;
	T * nullvalue; // pointer when in need of resetting
	T * circularbuffer;
	FixedCircularBuffer(size_t _size,size_t _fixed_size,T * _nullvalue) : size(_size),fixed_size(_fixed_size),nullvalue(_nullvalue)
	{ reset(); }
	~FixedCircularBuffer()
	{
		delete[] circularbuffer;
	}
	void reset()
	{
		circularbuffer=new T[size+fixed_size];
		for (int i=0;i<size+fixed_size;++i) circularbuffer[i]=*nullvalue; // fill fixed+buffer with nullvalue
	}
	int push(T element)
	{
		circularbuffer[pointer+fixed_size]=element;
		pointer++;
		pointer%=size;
		return pointer;
	}
	T operator[](size_t n)
	{ return circularbuffer[n]; }
};
