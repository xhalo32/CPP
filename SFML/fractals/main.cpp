#include <iostream>
#include <complex>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <string>

#include "main.h"

using namespace sf;
using namespace std;

typedef complex<float> com;

const int width=1600,height=900,CBSIZE=1000000;
float scale=4.0/width;
float center[]={2,1.1};
int iters=50;
int movestep=20;

RenderWindow win(VideoMode(width,height),"Fractals!");//,Style::Fullscreen);

int iterate(int iters, com c, com z=com(0)) // z is the start value
{
	for (int i=0;i<iters;++i)
	{
		z=z*z+c;
		if (abs(z)>2) return i;
	}
	return -1;
}

void writepixel(uint8_t*p,int x,int y,int value)
{
	if ((x>=0)&&(x<width))
		if ((y>=0)&&(x<height))
		{
			p[(width*y+x)*4]=value; // R?
			p[(width*y+x)*4+1]=value; // G?
			p[(width*y+x)*4+2]=value; // B?
			p[(width*y+x)*4+3]=255; // A?
		}
}

void render(Texture & tex,float sx=0,float sy=0,float sscale=1)
{ 
 	uint8_t *pixels = new uint8_t[4 * height * width];

	int value;
	for (int x=0;x<width;++x)
		for (int y=0;y<height;++y)
		{

			com c((x/sscale+sx)*scale-center[0], (y/sscale+sy)*scale-center[1]);
			int n=iterate(iters,c);

			value=0;
			if (n==-1) value=255;
			else value=n;

			float pervalue=pow((float)value/iters,0.5);
			(pervalue>1) ? pervalue=1 : true;
			writepixel(pixels,x,y,255*pervalue);
		}

	tex.update(pixels);

	delete[] pixels;
}

void renderPoints(CircularBuffer<FractalPoint> cb, float sx=0,float xy=0,float w=width, float h=height)
{
	int value;
	FractalPoint fp(0.f,0.f,0.f,0);
	for (int x=0;x<width;++x)
		for (int y=0;y<height;++y)
		{
			com c(x*scale-center[0], y*scale-center[1]);
			int n=iterate(iters,c);

			value=0;
			if (n==-1) value=255;
			else value=n;

			float pervalue=pow((float)value/iters,0.5);
			(pervalue>1) ? pervalue=1 : true;
			fp.x=x;fp.y=y;fp.side=1.f;fp.value=(int)255*pervalue;
			cb.push(fp);
		}
}

void drawFractalPoint(RenderWindow & win,FractalPoint fp)
{
	RectangleShape rect;
	rect.setSize(Vector2f(fp.side,fp.side));
	rect.setPosition(Vector2f(fp.x,fp.y));
	rect.setFillColor(Color(fp.value,fp.value,fp.value));
	win.draw(rect);
}

void drawCircularBuffer(RenderWindow & win,CircularBuffer<FractalPoint> cb,float x,float y,float w,float h)
{
	Texture tex; tex.create(width,height);
	Sprite sprite(tex);

 	uint8_t *pixels=new uint8_t[4 * height * width];

	for (int i=0;i<cb.size;++i)
	{
		FractalPoint fp=cb[i];
		writepixel(pixels,fp.x,fp.y,fp.value);
	}

	tex.update(pixels);
	sprite.setPosition(-x,-y);

	delete[] pixels;

	win.draw(sprite);
}

int main()
{
	FractalPoint _null(0.f,0.f,0.f,0);
	CircularBuffer<FractalPoint> cb(CBSIZE, &_null);

	Font font;
	font.loadFromFile("DejaVuSans.ttf");
	Text text("", font);
	text.setCharacterSize(30);
	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(2);

	renderPoints(cb);

	float timer=0, delay=0.1;
	float x=0,y=0,zoom=1;
	Clock clock;

	Event event;
	while (win.isOpen())
	{
		float time=clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;

        while (win.pollEvent(event))
        {
            if (event.type==Event::Closed)
                win.close();
			if (event.type==Event::KeyPressed)
			{
				if (event.key.code==Keyboard::Up) y-=movestep/zoom;
				else if (event.key.code==Keyboard::Down) y+=movestep/zoom;
				else if (event.key.code==Keyboard::Right) x+=movestep/zoom;
				else if (event.key.code==Keyboard::Left) x-=movestep/zoom;
				else if (event.key.code==Keyboard::W) zoom*=1.1;
				else if (event.key.code==Keyboard::S) zoom/=1.1;
				else if (event.key.code==Keyboard::R)
				{
					renderPoints(cb);
				}
			}
        }
		ostringstream oss; oss<<(int)x<<" "<<(int)y<<"\n"<<zoom<<"\n";
		text.setString(oss.str());

		if (timer>=delay)
		{
			timer=0;

			win.clear(Color::Black);
			drawCircularBuffer(win,cb,x,y,width/zoom,height/zoom);
			
			win.draw(text);
			win.display();
		}
	}
	return 0;
}
