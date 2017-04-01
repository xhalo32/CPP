#include <SFML/Graphics.hpp>
#include <time.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;

#include "utils.cpp"
#include "color.cpp"

#include "paddle.cpp"
#include "ball.cpp"


const int width = 600, height = 400;


RenderWindow window(VideoMode(width,height), "Ping Pong");
RenderWindow * windowp = &window;

Paddle pad1(-1, windowp);
Paddle pad2(1, windowp);

const int numpad = 2;
const int numballs = 2;

Paddle * padlist[] = {&pad1, &pad2};
Ball * balllist[numballs];


void loop_events(Event);
void loop();
void draw();
void generate_balls();


int main()
{
	generate_balls();

	Font font;
	font.loadFromFile("Ubuntu-L.ttf");

	float timer = 0, delay = 1.0 / 60;
	Clock clock;
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		float fps = 1.0 / timer;

		Event e;

		while (window.pollEvent(e))
		{
			loop_events(e);
		}

		if (timer > delay)
		{
			loop();

			window.clear(Color(231, 232, 235));

			draw();

			window.draw(msg(font, to_string(fps), 0, 0,
				16, 60, 60, 60, false));

			window.display();

			timer = 0;
		}
	}
	return 0;
}

void generate_balls()
{
	srand(time(0));
	for (int i = 0; i < numballs; i++)
	{
		balllist[i] = new Ball(windowp, i);
		balllist[i]->setColorHue(rand() % 255);
	}
}

void loop_events(Event e)
{
	if (e.type == Event::Closed)
		window.close();

	if (e.type == Event::KeyPressed)
	{
		if (e.key.code == Keyboard::Key::R) generate_balls();
	}

	for (int i = 0; i < numpad; i++)
	{
		padlist[i]->loop_events(e);
	}
}

void loop()
{

	for (int i = 0; i < numpad; i++)
	{
		padlist[i]->update();
	}

	for (int i = 0; i < numballs; i++)
	{
		if (!(balllist[i]->disabled))
			balllist[i]->update(padlist, numpad);
	}
}

void draw()
{
	for (int i = 0; i < numballs; i++)
	{
		if (!(balllist[i]->disabled))
			balllist[i]->draw();
	}
	for (int i = 0; i < numpad; i++)
	{
		padlist[i]->draw();
	}
}