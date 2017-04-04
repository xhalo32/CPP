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
	
	color[0] = 100;
	color[1] = 100;
	color[2] = 100;

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
void Paddle::draw(Paddle * padlist[2])
{
	//move the paddle to move the center of rotation
	double rad = sqrt(pow(width, 2) + pow(height, 2)) / 2.0;
	double stupidangle = atan(height/width);

	int pos[] = { 	(int)x + side * (int)(rad*cos(vy*M_PI/180. + stupidangle)), 
					(int)y },
		wh[] = { width, height };
			
	//windowp->draw(draw_rect(pos, wh, color));

	windowp->draw(draw_rect_angle(pos, wh, color, (int) vy * -side));

	int winner = 0;
	if (padlist[(-side+1)/2]->points < this->points) winner = 1;
	if (padlist[(-side+1)/2]->points > this->points) winner = -1;

	windowp->draw(msg(font, to_string(points),
		windowp->getSize().x / 2.0 + side * ( windowp->getSize().x / 5.0 ),
		10, 50 + 8*winner, 100 - 100*winner, 100 + 100*winner, 100, true));
}

void Paddle::addPoint()
{points++;}
void Paddle::resetPoints()
{points = 0;}
int Paddle::getWidth()
{return this->width;}
int Paddle::getX()
{return this->x;}
int Paddle::getHeight()
{return this->height;}
int Paddle::getY()
{return this->y;}
int Paddle::getSide()
{return this->side;}
float Paddle::getVy()
{return this->vy;}
float Paddle::getMaxspeed()
{return this->maxspeed;}