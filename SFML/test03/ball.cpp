#include "ball.h"
#include <cmath> //for fmod

Ball::Ball(RenderWindow * rwp, int index): windowp(rwp)
{
	x = windowp->getSize().x / 2 + rand() % (4*radius);
	y = windowp->getSize().y / 2 + rand() % (4*radius);

	angle = fmod(rand(), 360.0);
	acctime = rand() % 100 + 20;

	for (int i = 0; i < trailsize; ++i)
	{
		trail[i].x = -radius;
		trail[i].y = -radius;
	}

	vx = speed * cos(angle * M_PI / 180.);
	vy = speed * sin(angle * M_PI / 180.);
}
void Ball::update(Paddle * padlist[], int numpad,
				Ball * balllist[], int numballs)
{
	if (destroyed) return;

	timer += 1;
	angle = fmod(angle, 360.0);

	//test for borders
	if (y > windowp->getSize().y - radius)
	{
		angle += -2*angle;
		y = windowp->getSize().y - radius;

		if (abs(vx) / speed <.5)
		{
			angle += 30 * vx/abs(vx);
		}
	}
	else if (y < radius)
	{
		angle += -2*angle;
	 	y = radius;

		if (abs(vx) / speed <.5)
		{
			angle += - 30 * vx/abs(vx);
		}
	}

	if (!(disabled))
	{
		if (x < radius)
		{
			padlist[1]->addPoint();
			disabled = true;
		}

		else if (x > windowp->getSize().x - radius)
		{
			padlist[0]->addPoint();
			disabled = true;
		}
	}
	else
	{
		if (x < radius - trailsize*trailfreq*speed - radius)
		{
			destroyed = true;
		}

		else if (x > windowp->getSize().x + trailsize*trailfreq*speed)
		{
			destroyed = true;
		}
	}

	//test for paddles
	for (int i = 0; i < numpad; i++)
	{
		Paddle p = *padlist[i];

		if ((x < (int) p.getX() + p.getWidth()) &&
			(x > (int) p.getX()) &&
			(y < (int) p.getY() + p.getHeight()) &&
			(y > (int) p.getY()))
		{
			float vym = (speed * p.getSide() - speed * sin(angle*M_PI/180.));
			angle += 180 - 2*angle - vym * p.getVy();
			x = p.getX()+p.getWidth() * (1 - p.getSide()) / 2;

			lastPad = padlist[i];
		}
	}

	//test for other balls
	for (int i = 0; i < numballs; i++)
	{
		Ball * b = balllist[i];

		if (!(b == this))
			if ((x < (int) b->getX() + b->getRadius()) &&
				(x > (int) b->getX() - b->getRadius()) &&
				(y < (int) b->getY() + b->getRadius()) &&
				(y > (int) b->getY() - b->getRadius()))
			{
				//angle += 180 - 2*b->getAngle();

				int a1 = (int) this->angle;
				int a2 = b->getAngle();

				int halfa = a2 + (360-a2)/2 + a1/2;

				this->angle = 2*halfa - a1;
				b->setAngle(2*halfa - a2);
			}
	}

	if (speed < maxspeed) speed += maxspeed / acctime;

	vx = speed * cos(angle * M_PI / 180.);
	vy = speed * sin(angle * M_PI / 180.);

	if (timer % trailfreq == 0)
	{
		struct coord
		{
			int x;
			int y;
		} newtrail[trailsize];

		newtrail[0].x = x;
		newtrail[0].y = y;

		for (int i = 0; i < trailsize-1; i++)
		{
			newtrail[i+1].x = trail[i].x;
			newtrail[i+1].y = trail[i].y;
		}
		for (int i = 0; i < trailsize; ++i)
		{
			trail[i].x = newtrail[i].x;
			trail[i].y = newtrail[i].y;
		}
	}

	x += vx;
	y += vy;
}
void Ball::draw()
{
	if (destroyed) return;

	int r;
	int pos[2] = {0, 0};

	//trail
	for (int i = trailsize-1; i >= 0; i--)
	{
		RgbColor rgb1;
		rgb1.r = color[0];
		rgb1.g = color[1];
		rgb1.b = color[2];

		HsvColor hsv = RgbToHsv(rgb1);
		hsv.s -= i * hsv.s / trailsize;

		RgbColor rgb2 = HsvToRgb(hsv);

		int rgb[3];
		rgb[0] = rgb2.r;
		rgb[1] = rgb2.g;
		rgb[2] = rgb2.b;

		pos[0] = trail[i].x - radius * ((trailsize-i) / (float)trailsize);
		pos[1] = trail[i].y - radius * ((trailsize-i) / (float)trailsize);
		r = radius * ((trailsize-i) / (float)trailsize);


		windowp->draw(draw_circle(pos, r, rgb));
	}

	pos[0] = (int)x - radius;
	pos[1] = (int)y - radius;
	r = radius;

	windowp->draw(draw_circle(pos, r, color));
}
void Ball::setColorHue(int hue)
{
	HsvColor hsv;
	hsv.h = hue;
	hsv.s = 200;
	hsv.v = 255;
	RgbColor rgb;
	rgb = HsvToRgb(hsv);

	int col[3] = { (int) rgb.r, (int) rgb.g, (int) rgb.b };

	for (int i = 0; i < 3; ++i)
	{
		color[i] = col[i];
	}
}

float Ball::getX()
{return x;}
float Ball::getY()
{return y;}
float Ball::getAngle()
{return angle;}
void Ball::setAngle(int ang)
{angle = ang;}
int Ball::getRadius()
{return radius;}