/*
food.h
represents food in the game of snake

Food
	int type
	int x, y
	show()
*/

typedef struct
{
    //the x and y offsets of the food
    int x, y;

    //the type of food
    int type;

}Food;

food_init( Food * f, int x, int y, int type )
{
	f->x = x;
	f->y = y;
	f->type = type;
}

food_show( Food * f )
{
	SDL_Surface *temp = NULL;
	switch( f->type )
	{
		case APPLE:
			temp = apple;
			break;
		case DONUT:
			temp = donut;
			break;
	}

	apply_surface( f->x, f->y, temp, graphics.screen, NULL );
}