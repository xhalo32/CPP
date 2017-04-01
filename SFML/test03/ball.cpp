#include "ball.h"

Ball::Ball(RenderWindow * rwp, int index): windowp(rwp)
{
	x = windowp->getSize().x / 2;
	y = windowp->getSize().y / 2;

	angle = rand() % 360;
	acctime = rand() % 60 + 60;

	while (((angle > 45) && (angle < 90+45)) ||
		((angle > 180+45) && (angle < 180+90+45)))
	{
		angle = rand() % 360;
	}

	for (int i = 0; i < trailsize; ++i)
	{
		trail[i][0] = -radius;
		trail[i][1] = -radius;
	}

	vx = speed * cos(angle * M_PI / 180.);
	vy = speed * sin(angle * M_PI / 180.);
}
void Ball::update(Paddle * padlist[], int numpad)
{
	timer += 1;
	angle %= 360;

	//test for borders
	if (y > windowp->getSize().y - radius) 	angle += -2*angle;
	if (y < radius) 						angle += -2*angle;

	if (x < radius)
	{
		padlist[1]->addPoint();
		disabled = true;
	}

	if (x > windowp->getSize().x)
	{
		padlist[0]->addPoint();
		disabled = true;
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
			x = p.getX()+p.getWidth() * (-p.getSide() + 1) / 2;
		}
	}

	if (speed < maxspeed) speed += maxspeed / acctime;

	vx = speed * cos(angle * M_PI / 180.);
	vy = speed * sin(angle * M_PI / 180.);

	if (timer % trailfreq == 0)
	{
		int newtrail[trailsize][2];

		newtrail[0][0] = x;
		newtrail[0][1] = y;

		for (int i = 0; i < trailsize-1; i++)
		{
			newtrail[i+1][0] = trail[i][0];
			newtrail[i+1][1] = trail[i][1];
		}
		for (int i = 0; i < trailsize; ++i)
		{
			trail[i][0] = newtrail[i][0];
			trail[i][1] = newtrail[i][1];
		}
	}

	x += vx;
	y += vy;
}
void Ball::draw()
{
	int r;
	int pos[2] = {0, 0};

	//trail
	for (int i = 0; i < trailsize; i++)
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

		pos[0] = trail[i][0] - radius * ((trailsize-i) / (float)trailsize);
		pos[1] = trail[i][1] - radius * ((trailsize-i) / (float)trailsize);
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