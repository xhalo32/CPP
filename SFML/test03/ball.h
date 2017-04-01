class Ball
{
	public:
		Ball(RenderWindow *, int);
		void update(Paddle * [], int);
		void draw();

		void setColorHue(int);

		bool disabled = false;

	protected:
		float x, y, vx, vy,
			speed = 0, maxspeed = 6, acctime;

		int angle, radius = 8, trailsize = 10, 
			trailfreq = 4, timer = 0;


		int color[3];
		int trail[10][2];

		RenderWindow * windowp;
};