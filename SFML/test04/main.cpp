#include <time.h>

#include <math.h>
#include <sstream>
#include <iostream>

#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

const int width = 600, height = 400;
const int numdots = 3;
const int iterations = 4096;
const double fraction = 1./2;

int iter = 0;

struct dot
{
	int x;
	int y;
	void reset()
	{
		x = rand() % width;
		y = rand() % height;
	}
};
struct simpledot
{
	int x;
	int y;
};
dot dotarray[numdots];
dot roguedot;
simpledot drawndotarray[iterations];

RenderWindow window(VideoMode(width,height), "Chaos!");
RenderWindow * windowp = &window;


void loop_events(Event);
void loop();
void draw();
void reset();
Text msg(Font, string, int, int, int, int, int, int, bool);

int main()
{
	Font font;
	font.loadFromFile("Ubuntu-L.ttf");

	float timer = 0, delay = 1.0 / 200;
	Clock clock;

	srand(time(0));
	reset();
	
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
			window.clear(Color(231, 232, 235));

			if (iter < iterations)
			{
				loop();
				++iter;
			}

			draw();

			window.draw(msg(font, to_string(fps), 0, 0, 16, 60, 60, 60, false));

			window.display();

			timer = 0;
		}
	}
	return 0;
}

void loop_events(Event e)
{
	if (e.type == Event::Closed)
		window.close();

	if (e.type == Event::KeyPressed)
	{
		if (e.key.code == Keyboard::Key::R) reset();
	}
}
void loop()
{
	int dir = rand() % numdots;
	roguedot.x += (dotarray[dir].x - roguedot.x) * fraction;
	roguedot.y += (dotarray[dir].y - roguedot.y) * fraction;

	drawndotarray[iter].x = roguedot.x;
	drawndotarray[iter].y = roguedot.y;
}
void draw()
{
	CircleShape circle;

	sf::ConvexShape polygon;
	polygon.setPointCount(numdots);

	for (int i = 0; i < numdots; ++i)
	{
		/*circle.setRadius(3);
		circle.setFillColor(Color(50,50,50));
		circle.setPosition(dotarray[i].x, dotarray[i].y);

		windowp->draw(circle); */

		polygon.setPoint(i, sf::Vector2f(dotarray[i].x, dotarray[i].y));
	}
	polygon.setOutlineColor(Color(150,150,150));
	polygon.setFillColor(Color(0,0,0,0));
	polygon.setOutlineThickness(2);

	windowp->draw(polygon);

	for (int i = 0; i < iter; ++i)
	{
		circle.setRadius(2);
		circle.setFillColor(Color(50,150,50));
		circle.setPosition(drawndotarray[i].x, drawndotarray[i].y);

		windowp->draw(circle);
	}
	circle.setRadius(3);
	circle.setFillColor(Color(220,50,50));
	circle.setPosition(roguedot.x, roguedot.y);
	windowp->draw(circle);

}
void reset()
{
	for (int i = 0; i < numdots; ++i)
	{
		dotarray[i].reset();
	}
	roguedot.reset();

	iter = 0;
}

Text msg(Font f, string message,
	int x, int y, int fontsize, int R, int G, int B, bool center)
{
	Text text;
	text.setFont(f);
	text.setString(message);
	text.setCharacterSize(fontsize);
	text.setFillColor(Color(R,G,B));

	FloatRect rect = text.getLocalBounds();
	if (center)
	{ 	
		rect.left = x - (rect.width / 2.0f);
		rect.top = y - (rect.height / 2.0f);

		text.setPosition( rect.left, rect.top );
	}
	else
	{
		text.setPosition(x, y);
	}

	return text;
}
