#ifndef GAMEVALUES_H
	#include "gamevalues.h"
	#define GAMEVALUES_H
#endif
#include <ncurses.h>
#include <string.h>
#include <iostream>

const int relatives[][2]={ {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1} };

template <typename T>
struct memory
{
	size_t size;
	unsigned int pointer=0;
	T * buffer;
	T empty;

	memory(size_t _size, T _empty)
	{
		empty=_empty;
		size=_size;
		buffer=new T[size];
		for (int i=0; i<size; ++i) buffer[i]=empty;
	}
	bool push(T _object)
	{
		if (pointer==size) return false;
		buffer[pointer]=_object;
		++pointer;
		return true;
	}
	void flush()
	{
		buffer=new T[size];
		for (int i=0; i<size; ++i) buffer[i]=empty;
		pointer=0;
	}
};
typedef struct memory<int*> intarrmem;

void generate_mines2(intarrmem field, int amount, int width, int height)
{
	bool ok;
	int x,y;
	for (int i=0;i<amount;++i)
	{
		ok=false;
		int * arr=new int[2];
		while (!ok)
		{
			x=(std::rand())%(width);
			y=(std::rand())%(height);
			ok=true;

			for (int j=0;j<field.pointer;++j)
			{
				if ((x==field.buffer[j][0]) && (y==field.buffer[j][1]))
					ok=false;
			}
			arr[0]=x;arr[1]=y;
		}
		field.push(arr);
	}
}
void generate_tiles2(int ** tiles, intarrmem field, int width, int height)
{
	// 0 : no mines around
	// 1-8 : 1-8 mines around
	// 9 : mine itself
	
	int x,y;
	for (int i=0;i<field.size;++i)
	{
		x=field.buffer[i][0]+1; y=field.buffer[i][1]+1;
		for (int i=0;i<8;++i)
			tiles[x+relatives[i][0]][y+relatives[i][1]]++;
	}
	
	for (int l=0;l<field.size;++l) // redefine overridden bombs
	{
		tiles[field.buffer[l][0]+1][field.buffer[l][1]+1]=9;
	}
}
int ** mkboard(Values values)
{
	int _[2]={-1,-1};
	intarrmem minefield(values.mineamount,_);
	generate_mines2(minefield,values.mineamount,values.boardwidth,values.boardheight);
	int ** tiles;
	tiles=new int *[values.boardwidth+2];
	for (int i=0;i<values.boardwidth+2;++i)
	{
		tiles[i]=new int[values.boardheight+2];
		for (int j=0;j<values.boardheight+2;++j)
			tiles[i][j]=0;
	}
	generate_tiles2(tiles,minefield,values.boardwidth,values.boardheight);
	return tiles;
}
void drawboard(Values values, int ** tiles)
{
	for (int i=1;i<values.boardwidth+1;++i)
	for (int j=1;j<values.boardheight+1;++j)
	{
		if (tiles[i][j]==0)
		{
			attron(COLOR_PAIR(10));
			mvprintw(j+values.deltah,i+values.deltaw," ");
		}
		else if (tiles[i][j]==9)
		{
			attron(COLOR_PAIR(131));
			move(values.deltah+j,values.deltaw+i);
			addstr("\u2691");
		}
		else if ((tiles[i][j]>0)&&(tiles[i][j]<9))
		{
			switch(tiles[i][j])
			{
				case 1: attron(COLOR_PAIR(1)); break;
				case 2: attron(COLOR_PAIR(2)); break;
				case 3: attron(COLOR_PAIR(3)); break;
				default: attron(COLOR_PAIR(4)); break;
			}
			mvprintw(j+values.deltah,i+values.deltaw,"%d",tiles[i][j]);
		}

		attron(COLOR_PAIR(100));
	}
}

class Slider
{
public:
	int x,y,w,h,min,max,amount;
	int * value;
	char * name;
	Slider(const char * name, int x, int y, int w, int h, int min, int max, int amount, int * value) :
		name((char *) name),x(x),y(y),w(w),h(h),min(min),max(max),amount(amount),value(value){}
	void addval(int coefficient=1)
	{
		*value+=coefficient*amount;
		if (*value<=min) *value=min;
		if (*value>=max) *value=max;
	}
	void setmax() { *value=max; }
	void setmin() { *value=min; }
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

		char s[32];
		
		mvprintw(y,x,"%d",min);
		mvprintw(y,x+w+2-sprintf(s,"%d",max),"%d",max);
		mvprintw(y,x+w/2,"%d",*value);

		attron(COLOR_PAIR(100));
		mvhline(y+1,x+1,' ',w);
		attron(COLOR_PAIR(10));
		mvhline(y+1,x+1,' ',(int) (*value-min)*w/(max-min));
		attroff(COLOR_PAIR(10));

		if (bold) attroff(A_BOLD);
	}
};

void startmenu(Values &values)
{
	if (values.screenwidth>20+2) values.boardwidth=20;
	else values.boardwidth=values.screenwidth-2;
	if (values.screenheight>10+4) values.boardheight=10;
	else values.boardheight=values.screenheight-4;

	int selection=0;
	int h=1,w=20,x,y,ch,dh=0;
	if (values.screenheight>22) // if screen is big enought
		y=(values.screenheight-h)/2;
	else // if screen is less than 22 rows
	{
		y=values.screenheight/2-5+dh; dh=1;
	}
	if (values.screenwidth>22)
		w=20;
	else
		w=values.screenwidth-2;

	x=(values.screenwidth-w-1)/2;
	Slider mineslider("MINES \%",x,y,w,h,0,100,2,new int(10));
	Slider widthslider("WIDTH",x,y+5-dh,w,h,6,values.screenwidth-2,1,new int(values.boardwidth));
	Slider heightslider("HEIGHT",x,y+9-dh,w,h,6,values.screenheight-4,1,new int(values.boardheight));
	Slider * sliderselection=&mineslider;

	values.boardwidth=*widthslider.value;
	values.boardheight=*heightslider.value;
	values.mineamount=(values.boardheight*values.boardwidth)* *mineslider.value/100;
	if (values.mineamount>values.boardheight*values.boardwidth-25) values.mineamount=values.boardheight*values.boardwidth-25;
	values.deltaw=(values.screenwidth-values.boardwidth)/2-1;
	values.deltah=(values.screenheight-values.boardheight)/2;

	init_pair(221, COLOR_CYAN, COLOR_BLACK);
	init_pair(222, COLOR_GREEN, COLOR_BLACK);
	init_pair(223, COLOR_RED, COLOR_BLACK);
	init_pair(224, COLOR_BLUE, COLOR_BLACK);

	char title[4][84]={
		"   / | / /     /  |/  /  _/ | / / ____/ ___/ |     / / ____/ ____/ __ \\/ ____/ __ \\",
		"  /  |/ /_____/ /|_/ // //  |/ / __/  \\__ \\| | /| / / __/ / __/ / /_/ / __/ / /_/ /",
		" / /|  /_____/ /  / // // /|  / /___ ___/ /| |/ |/ / /___/ /___/ ____/ /___/ _, _/ ",
		"/_/ |_/     /_/  /_/___/_/ |_/_____//____/ |__/|__/_____/_____/_/   /_____/_/ |_|  "
	};

	bool start=false, torefresh=false;
	int ** tiles=mkboard(values);
	erase();
	while (!start)
	{
		erase();
		drawboard(values,tiles);

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
		attron(COLOR_PAIR(102));
		if (values.screenwidth>83)
			for (int i=0;i<4;++i)
				mvprintw(y/2-2+i,(values.screenwidth-83)/2,title[i]);
		else
		{
			attron(A_BOLD);
			attron(A_ITALIC);
			mvprintw(y/2,(values.screenwidth-13)/2,"N-MINESWEEPER");
			attroff(A_ITALIC);
			attroff(A_BOLD);
		}
		attron(COLOR_PAIR(100));

		refresh();

		ch=getch();

		if (selection==0) sliderselection=&mineslider;
		if (selection==1) sliderselection=&widthslider;
		if (selection==2) sliderselection=&heightslider;

		switch (ch)
		{
			case KEY_RIGHT: sliderselection->addval(); torefresh=true; break;
			case KEY_LEFT: sliderselection->addval(-1); torefresh=true; break;
			case KEY_PPAGE: sliderselection->setmax(); torefresh=true; break;
			case KEY_NPAGE: sliderselection->setmin(); torefresh=true; break;
			case 114: tiles=mkboard(values); break;
			case KEY_UP: selection--; break;
			case KEY_DOWN: selection++; break;
			case 32: start=true; break;
		}
		selection=(selection+3)%3;
		values.boardwidth=*widthslider.value;
		values.boardheight=*heightslider.value;
		values.mineamount=(values.boardheight*values.boardwidth)* *mineslider.value/100;
		if (values.mineamount>values.boardheight*values.boardwidth-25) values.mineamount=values.boardheight*values.boardwidth-25;
		values.deltaw=(values.screenwidth-values.boardwidth)/2-1;
		values.deltah=(values.screenheight-values.boardheight)/2;
		if (torefresh) { tiles=mkboard(values); torefresh=false; }
	}
}
