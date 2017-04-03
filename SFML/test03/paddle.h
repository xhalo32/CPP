class Paddle
{
public:
	Paddle(int, RenderWindow *);
	void update();
	void loop_events(Event);
	void draw(Paddle * padlist[2]);

	void addPoint();
	void resetPoints();

	int getWidth();
	int getX();

	int getHeight();
	int getY();

	int getSide();

	float getVy();
	float getMaxspeed();

protected:
	int width = 20,
		height = 100,
		side = 0,
		points = 0,
		color[3];

	float y = 20, x = 0,
		vy = 0, vx = 0,
		vvy = 0, vvx = 0,
		speedmult = 1,
		maxspeed = 6,
		decceleration = 0.8,
		acceleration = 0.4,
		borderresistance = 1;

	Font font;

	Keyboard::Key buttonUp;
	Keyboard::Key buttonDown;

	RenderWindow * windowp;
};