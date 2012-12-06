/*
snake.h
represents the snake

Snake
	x, y -int
	head -Segment
	body -Segment[]
	body_length -int
	handle_input()
	move()
	show()
	grow()
	check_collision()
*/

typedef struct
{
    //the x and y offsets of the snake
    int x, y;

    int prev_x, prev_y;

    //the directions the snake is moving
    int direction;

    //the head of the sanke!
    Segment head;

    //the snakes body
    Segment body[1024];

    //the length of the body
    int body_length;

}Snake;

void snake_init( Snake * s, int x, int y, int initial_length )
{
	s->x = x;
	s->y = y;
	s->prev_x = x;
	s->prev_y = y;
	s->body_length = 0;
	s->direction = UP;

	//make the head
	Segment tmp;
	segment_init( &tmp, s->x, s->y, SEGMENT_WIDTH, SEGMENT_HEIGHT, -1 );
	s->head = tmp;

	//initialize the body
	int i;
	for( i = 0; i < initial_length; i++ )
	{
		segment_init( &tmp, s->x, s->y + (SEGMENT_HEIGHT * (i + 1)), SEGMENT_WIDTH, SEGMENT_HEIGHT, i );
		s->body[i] = tmp;
		s->body_length++;
	}
}

void snake_show( Snake * s )
{
	//show the head
	SDL_Surface *tmp = NULL;
	switch( s->direction )
	{
		case UP: tmp = head; break;
		case DOWN: tmp = head_d; break;
		case LEFT: tmp = head_l; break;
		case RIGHT: tmp = head_r; break;
	}
	head_show( &s->head, tmp );

	//show the body
	int i;
	for( i = 0; i < s->body_length; i++ )
	{
		segment_show( &s->body[i] );
	}
}

void snake_move( Snake * s, int x, int y )
{
	int prev_x, prev_y, tmpx, tmpy;
	prev_x = s->head.x;
	prev_y = s->head.y;
	segment_move( &s->head, x, y );
	int i;
	for( i = 0; i < s->body_length; i++ )
	{
		tmpx = s->body[i].x;
		tmpy = s->body[i].y;
		segment_move( &s->body[i], prev_x, prev_y );
		prev_x = tmpx;
		prev_y = tmpy;
	}
}

void snake_grow( Snake * s )
{
	Segment tmp;
	segment_init( &tmp, -SEGMENT_WIDTH, -SEGMENT_HEIGHT, SEGMENT_WIDTH, SEGMENT_HEIGHT, s->body_length );
	s->body[s->body_length] = tmp;
	s->body_length++;
}

bool collision( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

int snake_check_collision( Snake * s, Food *food, int score, bool *game_over )
{
	//collision between head and body
	int i;
	SDL_Rect head;
	head.x = s->head.x;
	head.y = s->head.y;
	head.w = SEGMENT_WIDTH;
	head.h = SEGMENT_HEIGHT;
	for (i = 0; i < s->body_length; i++)
	{
		SDL_Rect seg;
		seg.x = s->body[i].x;
		seg.y = s->body[i].y;
		seg.w = SEGMENT_WIDTH;
		seg.h = SEGMENT_HEIGHT;

		if ( collision(head, seg) )
		{
			//play sound effect
	        if( Mix_PlayChannel( -1, ouch, 0 ) == -1 )
	        {
	            return 1;
	        }

			int num_removed = s->body_length - s->body[i].num;
			float percent = (float)num_removed / s->body_length;
			score -= (int)(score * percent);
			s->body_length = s->body[i].num;
			break;
		}
	}
	//collision between head and walls
	if ((s->head.x < 0) || ((s->head.x + SEGMENT_WIDTH) > graphics.screen_width) || (s->head.y < 0) || ((s->head.y + SEGMENT_HEIGHT) > graphics.screen_height))
	{
		(*game_over) = true;
	}
	//collision between head and food
	SDL_Rect seg;
	seg.x = (*food).x;
	seg.y = (*food).y;
	seg.w = SEGMENT_WIDTH;
	seg.h = SEGMENT_HEIGHT;
	if ( collision(head, seg ))
	{
		int j;
		for (j = -1; j < (*food).type; j++)
		{
			snake_grow( s );
			score += 10;
		}

		//play sound effect
        if( Mix_PlayChannel( -1, crunch, 0 ) == -1 )
        {
            return 1;
        }

		//move the food
		(*food).x = ( rand() % ( graphics.screen_width / SEGMENT_WIDTH ) ) * SEGMENT_WIDTH;
		(*food).y = ( rand() % ( graphics.screen_height / SEGMENT_HEIGHT ) ) * SEGMENT_HEIGHT;
		(*food).type = rand() % 2;

		//increase movement speed
		if ( FRAMES_PER_SECOND < MAX_FRAMES_PER_SECOND )
		{
			FRAMES_PER_SECOND++;
		}
	}

	return score;
}

void snake_handle_input( Snake * s )
{
	//If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
    	//if the snake is not in the same place the last time we checked for input then update direction.
    	if( ( s->prev_x != s->head.x ) || ( s->prev_y != s->head.y ) )
    	{
	    	//change the direction
	    	if( event.key.keysym.sym == controls.up )
	    	{
	    		if( s->direction != DOWN )
	        	{
	        		s->direction = UP;
	        		s->prev_x = s->head.x;
    				s->prev_y = s->head.y;
	        	} 
	    	}
	    	else if( event.key.keysym.sym == controls.down )
	    	{
	    		if( s->direction != UP)
	        	{
	        		s->direction = DOWN; 
	        		s->prev_x = s->head.x;
    				s->prev_y = s->head.y;
	        	}
	    	}
	    	else if( event.key.keysym.sym == controls.left )
	    	{
	    		if( s->direction != RIGHT)
	        	{
	        		s->direction = LEFT; 
	        		s->prev_x = s->head.x;
    				s->prev_y = s->head.y;
	        	}
	    	}
	    	else if( event.key.keysym.sym == controls.right )
	    	{
	    		if( s->direction != LEFT)
	        	{
	        		s->direction = RIGHT; 
	        		s->prev_x = s->head.x;
    				s->prev_y = s->head.y;
	        	}
	    	}
	    }
    }
}