#ifndef GAMEVALUES_H
	#include "gamevalues.h"
	#define GAMEVALUES_H
#endif
#include <ncurses.h>
#include <string.h>

class Slider
{
public:
	int x,y,w,h,min,max,amount;
	int * value;
	char * name;
	Slider(const char * name, int x, int y, int w, int h, int min, int max, int amount, int * value) :
		name((char *) name),x(x),y(y),w(w),h(h),min(min),max(max),amount(amount),value(value) {};
	void addval(int coefficient=1)
	{
		*value+=coefficient*amount;
		if (*value<=min) *value=min;
		if (*value>=max) *value=max;
	}
	void draw(bool bold=false)
	{
		if (bold) attron(A_BOLD);

		mvprintw(y+1,x-strlen(name)-1,"%s",name);
		mvaddch(y,x,ACS_ULCORNER);
		mvaddch(y,x+w+1,ACS_URCORNER);
		mvaddch(y+h+1,x,ACS_LLCORNER);
		mvaddch(y+h+1,x+w+1,ACS_LRCORNER);
		mvhline(y,x+1,ACS_HLINE,w);
		mvhline(y+h+1,x+1,ACS_HLINE,w);
		mvvline(y+1,x,ACS_VLINE,h);
		mvvline(y+1,x+w+1,ACS_VLINE,h);
		
		mvprintw(y-1,x,"%d",min);
		mvprintw(y-1,x+w,"%d",max);
		mvprintw(y-1,x+w/2,"%d",*value);

		attron(COLOR_PAIR(10));
		mvhline(y+1,x+1,' ',(int) *value*w/max);
		attroff(COLOR_PAIR(10));

		if (bold) attroff(A_BOLD);
	}
};

void startmenu(Values &values)
{
	if (values.screenwidth>20) values.boardwidth=20;
	else values.boardwidth=values.screenwidth;
	if (values.screenheight>10) values.boardheight=10;
	else values.boardheight=values.screenheight;

	int selection=0;
	int h=1,w=20,y=values.screenheight/2-h/2,x=values.screenwidth/2-w/2,ch;
	Slider mineslider("MINES \%",x,y,w,h,0,100,2,new int(10));
	Slider widthslider("WIDTH",x,y+5,w,h,2,values.screenwidth,1,new int(values.boardwidth));
	Slider heightslider("HEIGHT",x,y+9,w,h,2,values.screenheight,1,new int(values.boardheight));
	Slider * sliderselection=&mineslider;

	init_pair(221, COLOR_CYAN, COLOR_BLACK);
	init_pair(222, COLOR_GREEN, COLOR_BLACK);
	init_pair(223, COLOR_RED, COLOR_BLACK);
	init_pair(224, COLOR_BLUE, COLOR_BLACK);

	bool start=false;
	while (!start)
	{
		erase();
		switch (selection)
		{
			case 0:
				attron(COLOR_PAIR(221));
				mineslider.draw(true);
				attroff(COLOR_PAIR(221));
				
				widthslider.draw();
				heightslider.draw();
				break;
			case 1:
				attron(COLOR_PAIR(223));
				widthslider.draw(true);
				attroff(COLOR_PAIR(223));
				
				mineslider.draw();
				heightslider.draw();
				break;
			case 2:
				attron(COLOR_PAIR(224));
				heightslider.draw(true);
				attroff(COLOR_PAIR(224));
				
				mineslider.draw();
				widthslider.draw();
				break;
		}
		refresh();

		ch=getch();

		if (selection==0) sliderselection=&mineslider;
		if (selection==1) sliderselection=&widthslider;
		if (selection==2) sliderselection=&heightslider;

		switch (ch)
		{
			case KEY_RIGHT: sliderselection->addval(); break;
			case KEY_LEFT: sliderselection->addval(-1); break;
			case KEY_UP: selection--; break;
			case KEY_DOWN: selection++; break;
			case 32: start=true; break;
		}
		selection=(selection+3)%3;
	}
	values.boardwidth=*widthslider.value;
	values.boardheight=*heightslider.value;
	values.mineamount=(values.boardheight*values.boardwidth)* *mineslider.value/100;

	values.deltaw=values.screenwidth/2-values.boardwidth/2;
	values.deltah=values.screenheight/2-values.boardheight/2;

}
