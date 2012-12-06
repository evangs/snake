/*
game.h
represents the game

Game
	Snake player
	Food[] food //holds all food currently active
	int score
	bool game_over
	initialize()
	play()
*/

typedef struct
{
    //the player
    Snake player;

    //food
    Food food;

    //the players score
    int score;

    //bool to keep track if game is over or not
    bool game_over;

}Game;

void GameInit( Game * g )
{
	FRAMES_PER_SECOND = 5;
	g->score = 0;
	g->game_over = false;
	snake_init( &g->player, graphics.screen_width / 2, graphics.screen_height / 2, 3 );

	//init food
	int i;
	Food tmp;
	int x = ( rand() % ( graphics.screen_width / SEGMENT_WIDTH ) ) * SEGMENT_WIDTH;
	int y = ( rand() % ( graphics.screen_height / SEGMENT_HEIGHT ) ) * SEGMENT_HEIGHT;
	food_init( &tmp, x, y, 0 );
	g->food = tmp;
}

int GamePlay( Game * g )
{
	bool exit_now = false;
	bool quit = false;
	bool paused = false;

	//the frame rate regulator
    Timer fps;

    //keep track of the current fram
    int frame = 0;

	//While the user hasn't quit
    while( quit == false )
    {
    	//start the frame timer
        TimerStart( &fps );

        //While there's event to handle
        while( SDL_PollEvent( &event ) )
        {
        	if( event.type == SDL_KEYDOWN )
        	{
        		if( event.key.keysym.sym == controls.pause )
        		{
        			paused = paused ? false : true;
        		}
        	}

        	//handle player input
        	snake_handle_input( &g->player );

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
                exit_now = true;
            }
        }

        if ( !paused ) 
        {
        	if( Mix_PausedMusic() )
        	{
        		Mix_ResumeMusic();
        	}

	        switch( g->player.direction )
	        {
	        	case UP:
	        		snake_move( &g->player, g->player.head.x, g->player.head.y - SEGMENT_HEIGHT );
	        		break;
	        	case DOWN:
	        		snake_move( &g->player, g->player.head.x, g->player.head.y + SEGMENT_HEIGHT );
	        		break;
	        	case LEFT:
	        		snake_move( &g->player, g->player.head.x - SEGMENT_WIDTH, g->player.head.y );
	        		break;
	        	case RIGHT:
	        		snake_move( &g->player, g->player.head.x + SEGMENT_WIDTH, g->player.head.y );
	        		break;
	        }

	        //check for collisions
	        g->score = snake_check_collision( &g->player, &g->food, g->score, &quit );

	        //Fill screen
	    	SDL_FillRect( graphics.screen, &graphics.screen->clip_rect, SDL_MapRGB( graphics.screen->format, 0x80, 0x80, 0x80 ) );

	    	//show the food
	    	food_show( &g->food );

	        //show the snake
	        snake_show( &g->player );

	        //show the score
	        char score[100];
		    sprintf( score, "%d", g->score );

		    score_msg = TTF_RenderText_Solid( font, score, text_color );
		    apply_surface( ( graphics.screen_width - ( score_msg->w + 10) ), 10, score_msg, graphics.screen, NULL );
	    }
	    else
	    {
	    	//pause the music
	    	Mix_PauseMusic();

	    	//Fill screen
	    	SDL_FillRect( graphics.screen, &graphics.screen->clip_rect, SDL_MapRGB( graphics.screen->format, 0x80, 0x80, 0x80 ) );
	    	
	    	message = TTF_RenderText_Solid( font, "Paused", text_color );
	    	apply_surface( ( graphics.screen_width - message->w ) / 2, ( graphics.screen_height - message->h ) / 2, message, graphics.screen, NULL );
	    }

	    //Update the screen
        if( SDL_Flip( graphics.screen ) == -1 )
        {
            return 1;
        }

        //increment the frame counter
        frame++;

        //If we want to cap the frame rate
        if( TimerGetTicks( &fps ) < 1000 / FRAMES_PER_SECOND )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - TimerGetTicks( &fps ) );
        }
    }
    if( exit_now )
    {
    	return -1;
    }

    //if high score, get players name
    if( g->score > highscores.scores[0].score )
    {
    	quit = false;

    	//keep track of whether or not the user has entered their name
    	bool nameEntered = false;

	    //the gets the user's name
	    StringInput name;
	    StringInputInit( &name );

	    //set the message
	    message = TTF_RenderText_Solid( font, "High Score! Enter Your Name:", text_color );

	    //While the user hasn't quit
	    while( !quit )
	    {
	        //while there's events to handle
	        while( SDL_PollEvent( &event ) )
	        {
	            //If the user hasn't entered their name yet
	            if( nameEntered == false )
	            {
	                //Get user input
	                StringInputHandleInput( &name );

	                //If the enter key was pressed
	                if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
	                {
	                    //Change the flag
	                    nameEntered = true;
	                    quit = true;
	                }
	            }

	            //If the user has Xed out the window
	            if( event.type == SDL_QUIT )
	            {
	                //Quit the program
	                quit = true;
	            }
	        }

	        //Fill screen
    		SDL_FillRect( graphics.screen, &graphics.screen->clip_rect, SDL_MapRGB( graphics.screen->format, 0x80, 0x80, 0x80 ) );

	        //Show the message
	        apply_surface( ( graphics.screen_width - message->w ) / 2, ( ( graphics.screen_height / 2 ) - message->h ) / 2, message, graphics.screen, NULL );

	        //Show the name on the screen
	        StringInputShowCentered( &name );

	        //update the screen
	        if( SDL_Flip( graphics.screen ) == -1 )
	        {
	            return true;
	        }
	    }

	    Highscore hs;
	    hs.score = g->score;
	    strcpy( hs.name, name.str );
	    highscores_add_score( &highscores, hs );

	    StringInputDel( &name );
	}

    return 0;
}