#include <ncurses.h>
#include <unistd.h>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <locale.h>
#include <string.h>

#ifndef GAMEVALUES_H
	#include "gamevalues.h"
	#define GAMEVALUES_H
#endif

#ifndef SCREENS_H
	#include "screens.h"
	#define SCREENS_H
#endif

Values values;

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



void generate_mines(intarrmem field, int amount, int curx, int cury, int width, int height)
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

			if ((abs(x-curx)<=2)&&(abs(y-cury)<=2)) ok=false; // if mine is closer than 3 blocks from cursor
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
void generate_tiles(int ** tiles, intarrmem field, int width, int height)
{
	// 0 : no mines around
	// 1-8 : 1-8 mines around
	// 9 : mine itself
	// +10 : flag
	// +20 : opened
	
	/*for (int l=0;l<field.size;++l)
	{
		tiles[field.buffer[l][0]+1][field.buffer[l][1]+1]=9;
	}*/
	
	int x,y;
	for (int i=0;i<field.size;++i)
	{
		x=field.buffer[i][0]+1; y=field.buffer[i][1]+1;
		tiles[x+1][y]++;
		tiles[x+1][y+1]++;
		tiles[x][y+1]++;
		tiles[x-1][y+1]++;
		tiles[x-1][y]++;
		tiles[x-1][y-1]++;
		tiles[x][y-1]++;
		tiles[x+1][y-1]++;
	}
	
	for (int l=0;l<field.size;++l) // redefine overridden bombs
	{
		tiles[field.buffer[l][0]+1][field.buffer[l][1]+1]=9;
	}
}
void opentiles(int**,int,int,int,int); // prototype
void opentile(int ** tiles, int x, int y, int w, int h)
{
	if ((0<tiles[x][y])&&(tiles[x][y]<10)) // if the tile is closed and has bombs around it
	{
		tiles[x][y]+=20; // mark the tile open
		return;
	}
	if (tiles[x][y]==0) // if the tile is closed and has no bombs around
	{
		opentiles(tiles,x,y,w,h);
	}
}
void opentiles(int ** tiles, int x, int y, int w, int h)
{
	if ((tiles[x][y]<10)&&(x==0)||(x==w+1)||(y==0)||(y==h+1)) // if the tile is over the edge and is closed (tile is outside of the screen)
	{
		tiles[x][y]+=20; // mark the tile open
		return;
	}
	if ((0<tiles[x][y])&&(tiles[x][y]<10)) // if the tile is closed and has bombs around it
	{
		tiles[x][y]+=20; // mark the tile open
		return;
	}
	if ((10<=tiles[x][y])&&(tiles[x][y]<20)) // return if hit flag
	{ return; }
	if (tiles[x][y]==20) // return if already open empty
	{ return; }
	if ((20<tiles[x][y])&&(tiles[x][y]<30)) // if tile is open and has bombs around it
	{
		// count all the flags around it
		int numflags=0;
		for (int i=0;i<8;++i)
			if ((tiles[x+relatives[i][0]][y+relatives[i][1]]>=10)&&(tiles[x+relatives[i][0]][y+relatives[i][1]]<20)) numflags++;

		if (numflags==tiles[x][y]-20) // flags match number
			for (int i=0;i<8;++i)
				opentile(tiles,x+relatives[i][0],y+relatives[i][1],w,h);
	}
	if (tiles[x][y]==0) // if the tile is closed and has no bombs around
	{
		tiles[x][y]+=20; // open the tile

		opentiles(tiles, x+1, y  ,w,h);
		opentiles(tiles, x+1, y+1,w,h);
		opentiles(tiles, x  , y+1,w,h);
		opentiles(tiles, x-1, y+1,w,h);
		opentiles(tiles, x-1, y  ,w,h);
		opentiles(tiles, x-1, y-1,w,h);
		opentiles(tiles, x  , y-1,w,h);
		opentiles(tiles, x+1, y-1,w,h);
	}
}
void flagtile(int ** tiles, int x, int y)
{
	if ((tiles[x][y]>=0)&&(tiles[x][y]<10)) tiles[x][y]+=10; // flag
	else if ((tiles[x][y]>=10)&&(tiles[x][y]<20)) tiles[x][y]-=10; // unflag
}
void resettiles(int **& tiles, Values values)
{
	for (int i=0;i<values.boardwidth+2;++i)
		for (int j=0;j<values.boardheight+2;++j)
			tiles[i][j]=0; // set all tiles as 0
}

int main()
{
	setlocale(LC_ALL,"");

	WINDOW * window;
	std::srand(std::time(0)); // use current time as seed for random generator

	window=initscr();
	int WINWIDTH,WINHEIGHT;
	getmaxyx(stdscr,WINHEIGHT,WINWIDTH);
	values.screenwidth=WINWIDTH;
	values.screenheight=WINHEIGHT;

	int x,y;
	int ch;
	int flags=0,goodflags=0,unopened=0;

	bool fail=false;
	bool firsttile=true;

	if(has_colors() == FALSE) {	endwin(); std::cout<<"Your terminal does not support color"<<std::endl; exit(1); }
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_WHITE); // number 1
	init_pair(2, COLOR_GREEN, COLOR_WHITE); // number 2
	init_pair(3, COLOR_RED, COLOR_WHITE); // number 3
	init_pair(4, COLOR_BLUE, COLOR_WHITE); // numbers 4-8
	init_pair(9, COLOR_BLACK, COLOR_RED); // mine
	init_pair(10, COLOR_WHITE, COLOR_WHITE); // open cell
	init_pair(100, COLOR_WHITE, COLOR_BLACK); // closed cell (default color)
	init_pair(101, COLOR_RED, COLOR_BLACK); // fail color
	init_pair(102, COLOR_GREEN, COLOR_BLACK); // win color

	// with cursor
	init_pair(11, COLOR_CYAN, COLOR_YELLOW);
	init_pair(12, COLOR_GREEN, COLOR_YELLOW);
	init_pair(13, COLOR_RED, COLOR_YELLOW);
	init_pair(14, COLOR_BLUE, COLOR_YELLOW);
	init_pair(19, COLOR_BLACK, COLOR_YELLOW);
	init_pair(20, COLOR_WHITE, COLOR_YELLOW);
	init_pair(200, COLOR_WHITE, COLOR_YELLOW);

	init_pair(130, COLOR_RED, COLOR_BLACK); // flag without cursor
	init_pair(131, COLOR_BLACK, COLOR_WHITE); // correct flags

	noecho();
	curs_set(0);
	keypad(stdscr,TRUE);
	
	startmenu(values);
	x=values.boardwidth/2; y=values.boardheight/2;

	int _empty[2]={-1,-1};
	intarrmem minefield(values.mineamount,_empty);

	int **tiles;
	tiles=new int*[values.boardwidth+2];
	for(int i=0;i<values.boardwidth+2;++i)
	{
		tiles[i]=new int[values.boardheight+2];
		for (int j=0;j<values.boardheight+2;++j)
			tiles[i][j]=0;
	}

	while (1)
	{
		flags=goodflags=unopened=0;

		// DRAW
		erase();

		for (int i=1;i<values.boardwidth+1;++i)
		for (int j=1;j<values.boardheight+1;++j)
		{
			if ((20<tiles[i][j])&&(tiles[i][j]<29)) // if tile is open and not a mine and not flagged
			{
				switch(tiles[i][j])
				{
					case 21:
						attron(COLOR_PAIR(1+10*((i==x)&&(j==y)))); break;
					case 22:
						attron(COLOR_PAIR(2+10*((i==x)&&(j==y)))); break;
					case 23:
						attron(COLOR_PAIR(3+10*((i==x)&&(j==y)))); break;
					default:
						attron(COLOR_PAIR(4+10*((i==x)&&(j==y)))); break;
				}

				mvprintw(values.deltah+j,values.deltaw+i,"%d",tiles[i][j]-20);
			}
			else if (tiles[i][j]==20) // if tile is open and has no mines around it
			{
				attron(COLOR_PAIR(10+10*((i==x)&&(j==y))));
				mvprintw(values.deltah+j,values.deltaw+i," ");
			}
			else if (tiles[i][j]==29) // if tile is open and is a mine
			{
				attron(COLOR_PAIR(9+10*((i==x)&&(j==y))));
				mvprintw(values.deltah+j,values.deltaw+i,"X");
				fail=true;
			}
			else if ((tiles[i][j]>=10)&&(tiles[i][j]<20)) // flag
			{
				if (tiles[i][j]==19) // if flag is on a mine
					goodflags++;
				attron(COLOR_PAIR(130-117*((i==x)&&(j==y))));
				move(values.deltah+j,values.deltaw+i);
				addstr("\u2691");
				flags++;
			}
			else // if the tile is closed
			{
				unopened++;
				attron(COLOR_PAIR(100+100*((i==x)&&(j==y))));
				mvprintw(values.deltah+j,values.deltaw+i," ");
			}

			/*if (tiles[i][j]==9) // if tile is a mine (DEBUG)
			{
				attron(COLOR_PAIR(3));
				mvprintw(j,i,"X");
			}*/

			attron(COLOR_PAIR(100));
		}

		// draw a border
		if (fail) attron(COLOR_PAIR(101)); if ((goodflags==values.mineamount)&&(unopened==0)) attron(COLOR_PAIR(102));
		mvaddch(values.deltah,values.deltaw,ACS_ULCORNER);
		mvaddch(values.deltah,values.deltaw+values.boardwidth+1,ACS_URCORNER);
		mvaddch(values.deltah+values.boardheight+1,values.deltaw,ACS_LLCORNER);
		mvaddch(values.deltah+values.boardheight+1,values.deltaw+values.boardwidth+1,ACS_LRCORNER);
		mvhline(values.deltah,values.deltaw+1,ACS_HLINE,values.boardwidth);
		mvhline(values.deltah+values.boardheight+1,values.deltaw+1,ACS_HLINE,values.boardwidth);
		mvvline(values.deltah+1,values.deltaw,ACS_VLINE,values.boardheight);
		mvvline(values.deltah+1,values.deltaw+values.boardwidth+1,ACS_VLINE,values.boardheight);
		if (fail) attroff(COLOR_PAIR(101)); if ((goodflags==values.mineamount)&&(unopened==0)) attroff(COLOR_PAIR(102));

		char s[10];
		sprintf(s,"%d %d",values.boardwidth,values.boardheight);
		mvprintw(values.deltah-1,values.deltaw+values.boardwidth-strlen(s),s);
		attron(COLOR_PAIR(130));
		mvprintw(values.deltah-1,values.deltaw+1,"%d",values.mineamount-flags);

		char s2[]="N-MINESWEEPER";
		attron(COLOR_PAIR(102));
		attron(A_BOLD);
		attron(A_ITALIC);
		mvprintw(values.deltah/2-1,(values.screenwidth-strlen(s2))/2,s2);
		attron(COLOR_PAIR(100));
		attroff(A_ITALIC);
		attroff(A_BOLD);


		refresh();

		// UPDATE

		if (fail)
		{
			// open the whole board
			for (int i=1;i<values.boardwidth+1;++i)
			for (int j=1;j<values.boardheight+1;++j)
			{
				if ((0<tiles[i][j])&&(tiles[i][j]<9))
				{
					switch(tiles[i][j])
					{
						case 1:
							attron(COLOR_PAIR(1+10*((i==x)&&(j==y)))); break;
						case 2:
							attron(COLOR_PAIR(2+10*((i==x)&&(j==y)))); break;
						case 3:
							attron(COLOR_PAIR(3+10*((i==x)&&(j==y)))); break;
						default:
							attron(COLOR_PAIR(4+10*((i==x)&&(j==y)))); break;
					}
					mvprintw(values.deltah+j,values.deltaw+i,"%d",tiles[i][j]);
				}
				else if (tiles[i][j]==9)
				{
					attron(COLOR_PAIR(9+10*((i==x)&&(j==y))));
					mvprintw(values.deltah+j,values.deltaw+i,"X");
				}
				else if (tiles[i][j]==0)
				{
					attron(COLOR_PAIR(10+10*((i==x)&&(j==y))));
					mvprintw(values.deltah+j,values.deltaw+i," ");
				}
				else if ((tiles[i][j]>=10)&&(tiles[i][j]<19)) // fail flag
				{
					attron(COLOR_PAIR(9));
					move(values.deltah+j,values.deltaw+i);
					addstr("\u2691");
				}
				else if (tiles[i][j]==19){
					attron(COLOR_PAIR(131));
					move(values.deltah+j,values.deltaw+i);
					addstr("\u2691");
				}
				attron(COLOR_PAIR(100));
			}
			
			attron(A_BOLD);
			mvprintw(values.deltah,values.deltaw+(values.boardwidth-strlen("FAIL"))/2+1,"FAIL");
			attroff(A_BOLD);
			refresh();

			// stop user input
			while (1) {	ch=getch(); if (ch==114) { fail=false; firsttile=true; minefield.flush(); resettiles(tiles,values); x=values.boardwidth/2; y=values.boardheight/2; timeout(0); break; } } }

		if ((goodflags==values.mineamount)&&(unopened==0)) while (1) { attron(A_BOLD); mvprintw(values.deltah,values.deltaw+(values.boardwidth-strlen("DONE"))/2+1,"DONE"); attroff(A_BOLD); refresh(); ch=getch(); if (ch==114) { firsttile=true; minefield.flush(); resettiles(tiles,values); x=values.boardwidth/2; y=values.boardheight/2; timeout(0); break; } }

		ch=getch();
		switch (ch)
		{
			case 97: case KEY_LEFT: x--; break;
			case 100: case KEY_RIGHT: x++; break;
			case 119: case KEY_UP: y--; break;
			case 115: case KEY_DOWN: y++; break;
			case 65: x-=2; break;
			case 68: x+=2; break;
			case 87: y-=2; break;
			case 83: y+=2; break;
			case 32: if (firsttile) { generate_mines(minefield,values.mineamount,x-1,y-1,values.boardwidth,values.boardheight); generate_tiles(tiles,minefield,values.boardwidth,values.boardheight); firsttile=false; }
				opentiles(tiles,x,y,values.boardwidth,values.boardheight);
				break;
			case 70: case 102: flagtile(tiles,x,y); break;
		}
		if (x<1)x=1;
		if (x>values.boardwidth)x=values.boardwidth;
		if (y<1)y=1;
		if (y>values.boardheight)y=values.boardheight;
	}
}
