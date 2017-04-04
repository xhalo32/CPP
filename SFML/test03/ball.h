class Ball
{
public:
	Ball(RenderWindow *, int);
	void update(Paddle * [], int, Ball *[], int);
	void draw();

	void setColorHue(int);

	float getX();
	float getY();
	float getAngle();

	void setAngle(int);

	int getRadius();

	bool disabled = false;
	bool destroyed = false;

protected:
	float x, y, vx, vy, angle,
		speed = 0, maxspeed = 6, acctime;

	int radius = 8,
		trailfreq = 3, timer = 0;

	const static int trailsize = 10;

	struct coord
	{
		int x;
		int y;
	} trail[trailsize];

	Paddle * lastPad;


	int color[3];

	RenderWindow * windowp;
};