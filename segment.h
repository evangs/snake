/*
segment.h
represents a segment of the snake in the game.

Segment
	x, y, w, h -int
	num -int
	show()
	move()
*/

typedef struct
{
    //the x and y offsets of the segment as well as width and height
    int x, y, w, h;

    //the number of the segment
    int num;

}Segment;

void segment_init( Segment * s, int x, int y, int w, int h, int n )
{
	s->x = x;
	s->y = y;
	s->w = w;
	s->h = h;
	s->num = n;
}

void segment_show( Segment * s )
{
	apply_surface( s->x, s->y, body, graphics.screen, NULL );
}

void head_show( Segment * s, SDL_Surface *head_surface )
{
	apply_surface( s->x, s->y, head_surface, graphics.screen, NULL );
}

void segment_move( Segment * s, int newX, int newY )
{
	s->x = newX;
	s->y = newY;
}