#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
#include <sstream>
#include <iostream>
using namespace sf;



const int M = 10, N = 10;
const int size = 32;
const int width = M*size, height = N*size;
const int size_at_start = 5;
const int max_snake = M*N;

int direction, length = size_at_start;

struct Apple
{ int x, y; } apple;

struct Snake
{ int x, y; } s[ max_snake ];

RectangleShape draw_rect( int pos[ 2 ], int size[ 2 ], int color[ 3 ] )
{ 
	RectangleShape rect;
	rect.setSize( Vector2f( size[ 0 ], size[ 1 ] ) );
	rect.setFillColor( Color( color[ 0 ], color[ 1 ], color[ 2 ] ) );
	rect.setPosition( pos[ 0 ], pos[ 1 ] );

	return rect;
}

Text msg ( Font f, std::string message, int x, int y, int fontsize, int R, int G, int B, bool center )
{ 
	Text text;
	text.setFont(f);
	text.setString( message );
	text.setCharacterSize( fontsize );
	text.setColor(Color( R,G,B ));

	FloatRect rect = text.getLocalBounds();
	if (center)
	{ 	
		rect.left = x - (rect.width / 2.0f);
		rect.top = y - (rect.height / 2.0f);

		text.setPosition( rect.left, rect.top );
	}
	else
	{
		text.setPosition( x, y );
	}

	return text;
}




std::string Convert (float number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();   
}

std::string Convert (int number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();   
}

void generate_apple(  )
{ 	
	bool done;
	do
	{ 
		done = true;
		apple.x = rand(  ) % M;
		apple.y = rand(  ) % N;
		for ( int i = max_snake - length; i<max_snake; i++ )
		{ 
			if( ( apple.x == s[ i ].x ) && ( apple.y == s[ i ].y ) ) done = false;
		}
	} while ( !done );
}





int main(  )
{ 



	srand( time( 0 ) );

	Font font;
	font.loadFromFile("Ubuntu-L.ttf");	




	for ( unsigned int i=0; i<max_snake - size_at_start; i++ )
	{ 
		s[ i ].x = -1; s[ i ].y = -1;
	}

	for ( unsigned int i=max_snake; i>=max_snake - size_at_start; i-- )
	{ 
		s[ i ].x = M / 2; s[ i ].y = N / 2;
	}

	/*
	for ( unsigned int i=0; i<sizeof( s )/sizeof( s[ 0 ] ); i++ )
	{ 
		printf( "%d %d\n", s[ i ].x, s[ i ].y );
	}
	*/

	RenderWindow window( VideoMode( width,height ), "Snake Game" );

	float timer = 0, delay = 0.35;

	Clock clock;

	Snake snake;

	direction = 1;
	bool active = true;

	generate_apple(  );



	while ( window.isOpen(  ) && active )
	{ 
		float time = clock.getElapsedTime(  ).asSeconds(  );
		clock.restart(  );
		timer += time;


		Event e;
		while ( window.pollEvent( e ) )
		{ 
			if ( e.type == Event::Closed )
				window.close(  );


			/*
			if ( e.type == Event::TextEntered )
				std::cout << e.text.unicode << std::endl;
			*/
			if ( e.type == Event::KeyPressed )
				if ( ( e.key.code == Keyboard::Up ) 	&& 	!( direction == 2 ) ) direction = 0;
				if ( ( e.key.code == Keyboard::Right ) 	&& 	!( direction == 3 ) ) direction = 1;
				if ( ( e.key.code == Keyboard::Down ) 	&& 	!( direction == 0 ) ) direction = 2;
				if ( ( e.key.code == Keyboard::Left ) 	&& 	!( direction == 1 ) ) direction = 3;
		}


		if ( timer > delay )
		{
			timer = 0;



			for ( unsigned int i=max_snake - length + 1; i<max_snake; i++ )
			{ 
				/*
				printf(
					"%d %d --- %d %d\n\n", s[ i-1 ].x,s[ i-1 ].y,s[ i ].x,s[ i ].y );
				*/
				s[ i-1 ] = s[ i ];
			}


			// MOVE
			if ( direction == 0 ) s[ max_snake -1 ].y--;
			if ( direction == 1 ) s[ max_snake -1 ].x++;
			if ( direction == 2 ) s[ max_snake -1 ].y++;
			if ( direction == 3 ) s[ max_snake -1 ].x--;



			//TEST FOR APPLE
			if ( ( s[ max_snake-1 ].x == apple.x ) && ( s[ max_snake-1 ].y == apple.y ) ) { generate_apple(  ); length++; }


			//TEST FOR WALLS
			if ( 	( s[ max_snake -1 ].x >= M ) 	||
					( s[ max_snake -1 ].x < 0 ) 	||
					( s[ max_snake -1 ].y >= N ) 	||
					( s[ max_snake -1 ].y < 0 ) 	) 	
				{ 
					window.draw(msg( font, "You hit a wall!", width / 2.0f, height / 5.0f, 40, 0, 100, 180, true ) );
					window.draw(msg( font, "Score " + Convert( length - size_at_start ), width / 2.0f, height / 3.0f, 40, 0, 100, 0, true ) );
					active = false;
				}


			//TEST FOR SNAKE
			if ( length > size_at_start )
			{
				for ( int i=0; i<max_snake-1; i++ )
				{ 
					if ( ( s[ i ].x == s[ max_snake-1 ].x ) && ( s[ i ].y == s[ max_snake-1 ].y ) )
					{
						window.draw(msg( font, "You hit yourself!", width / 2.0f, height / 5.0f, 40, 0, 100, 180, true ) );
						window.draw(msg( font, "Score " + Convert( length - size_at_start ), width / 2.0f, height / 3.0f, 40, 0, 100, 0, true ) );
						active = false;
						break;
					}

				}
			}


			/*
			for ( unsigned int i=0; i<sizeof( s )/sizeof( s[ 0 ] ); i++ )
			{ 
				printf( "%d %d\n", s[ i ].x, s[ i ].y );
			}
			*/
		}

				
			// DRAW
		if ( active )
		{ 
			window.clear( Color( 232, 232, 232 ) );

			int pos[] = { size*apple.x + 2,size*apple.y + 2 }, wh[] = { size - 4,size - 4 }, color[] = { 225,0,0 };
			window.draw( draw_rect( pos, wh, color ) );


			for ( unsigned int i=0; i<max_snake; i++ )
			{ 
				if ( !( s[ i ].x == -1 ) && !( s[ i ].y == -1 ) )
				{ 

					int pos[] = { size*s[ i ].x + 1,size*s[ i ].y + 1 }, wh[] = { size - 2,size - 2 }, color[] = { 0,225,0 };

					int newcolor[ 3 ];
					for ( int j=0;j<3;j++ )
					{ 
						newcolor[ j ] = color[ j ] - color[ j ] / 2.0 / length * (max_snake- i);
					}

					window.draw( draw_rect( pos, wh, newcolor ) );

				}
			}
			window.draw(
					msg( font, "Score " + Convert( length - size_at_start ), 6,6, 20, 50, 50, 240, false )
				);

			window.display(  );
		}
		

	}

	window.display(  );

	while ( window.isOpen(  ) )
	{ 
		Event e;
		while ( window.pollEvent( e ) )
		{ 
			if ( e.type == Event::Closed )
				window.close(  );
		}

	}



	return 0;
}