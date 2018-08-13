#include <ncurses.h>
#include <unistd.h>
#include <chrono>
#include <iostream>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

int main()
{
	int x,y;
	int ch;
	int vx=1,vy=0;
	int looptime=100;

	initscr();
	if(has_colors() == FALSE)
	{	
		endwin();
		std::cout<<"Your terminal does not support color"<<std::endl;
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK); // green
	init_pair(2, COLOR_RED, COLOR_BLACK);   // red
	init_pair(3, COLOR_WHITE, COLOR_BLACK); // white
	noecho();
	curs_set(0);
	keypad(stdscr,TRUE);

	x=10; y=10;

    auto start = Time::now();

	while (1)
	{
		timeout(looptime);
		auto then=Time::now();
		ch=getch();
		if (ch==KEY_LEFT)
			{vx=-1; vy=0;}
		if (ch==KEY_RIGHT)
			{vx=1; vy=0;}
		if (ch==KEY_UP)
			{vx=0; vy=-1;}
		if (ch==KEY_DOWN)
			{vx=0; vy=1;}
		x+=vx; y+=vy;

		erase();
		auto now=Time::now(); fsec fs = now - then; ms d = std::chrono::duration_cast<ms>(fs);
		attron(COLOR_PAIR(2));
		mvprintw(0,0,"update took: %dms",d.count());
		attron(COLOR_PAIR(1));
		mvprintw(y,2*x,"m");
		refresh();
	}
}
