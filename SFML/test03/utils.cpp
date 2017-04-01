RectangleShape draw_rect(int pos[2], int size[2], int color[3])
{ 
	RectangleShape rect;
	rect.setSize(Vector2f(size[0],size[1]));
	rect.setFillColor(Color(color[0],color[1],color[2]));
	rect.setPosition(pos[0],pos[1]);

	return rect;
}

CircleShape draw_circle(int pos[2],int radius,int color[3] )
{ 
	CircleShape circle;
	circle.setRadius(radius);
	circle.setFillColor(Color(color[0],color[1],color[2]));
	circle.setPosition(pos[0],pos[1]);

	return circle;
}

Text msg (Font f, string message,
	int x, int y, int fontsize, int R, int G, int B, bool center)
{ 
	Text text;
	text.setFont(f);
	text.setString(message);
	text.setCharacterSize(fontsize);
	text.setFillColor(Color(R,G,B));

	FloatRect rect = text.getLocalBounds();
	if (center)
	{ 	
		rect.left = x - (rect.width / 2.0f);
		rect.top = y - (rect.height / 2.0f);

		text.setPosition( rect.left, rect.top );
	}
	else
	{
		text.setPosition(x, y);
	}

	return text;
}