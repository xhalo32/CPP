#include "paddle.h"

Paddle::Paddle(int side, RenderWindow * wp) : side(side), windowp(wp)
{

	if(side == -1)
	{
		buttonUp = Keyboard::Key::W;
		buttonDown = Keyboard::Key::S;
		this->x = 20;
	}
	else if(side == 1)
	{
		buttonUp = Keyboard::Key::Up;
		buttonDown = Keyboard::Key::Down;
		x = windowp->getSize().x-20-width;
	}

	this->font.loadFromFile("Ubuntu-L.ttf");	

}
void Paddle::update()
{
	// acceleretaion
	if ((vy > -0.001) && (vy < 0.001)) vy = 0;
	vy += vvy;
	if (vy > maxspeed) vy = maxspeed;
	if (vy < -maxspeed) vy = -maxspeed;
	if (vvy == 0) vy *= decceleration;

	if (y > windowp->getSize().y - vy - height) vy -= borderresistance;
	if (y < maxspeed-vy) vy += borderresistance;


	y += vy * speedmult;
}
void Paddle::loop_events(Event e)
{
	if (e.type == Event::KeyPressed)	
	{
		if (e.key.code == this->buttonUp)
			vvy = -acceleration;

		if (e.key.code == this->buttonDown)
			vvy = acceleration;
 
	}else if (e.type == Event::KeyReleased)
	{
		if ((e.key.code == this->buttonUp) &&
			(vvy < 0))
			vvy = 0;

		if ((e.key.code == this->buttonDown) &&
			(vvy > 0))
			vvy = 0;
	}
}
void Paddle::draw()
{
	int pos[] = { (int)x, (int)y },
		wh[] = { width, height },
		color[] = { 100,100,100 };
			
	windowp->draw(draw_rect(pos, wh, color));

	windowp->draw(msg(font, to_string(points),
		windowp->getSize().x / 2.0 + side * ( windowp->getSize().x / 5.0 ), 0,
		32, 60, 60, 60, false));
}

void Paddle::addPoint()
{
	points++;
}
int Paddle::getWidth()
{
	return this->width;
}
int Paddle::getX()
{
	return this->x;
}
int Paddle::getHeight()
{
	return this->height;
}
int Paddle::getY()
{
	return this->y;
}
int Paddle::getSide()
{
	return this->side;
}
float Paddle::getVy()
{
	return this->vy;
}
float Paddle::getMaxspeed()
{
	return this->maxspeed;
}