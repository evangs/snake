/*
highscores_menu.h

author: Evan Sailer, 11/27/2012

*/

highscores_show( Highscores * h )
{
	bool exit_now = false;
	bool quit = false;

	//While the user hasn't quit
    while( quit == false )
	{
    	//While there's event to handle
        while( SDL_PollEvent( &event ) )
        {
        	//If a mouse button was pressed
		    if( event.type == SDL_MOUSEBUTTONDOWN )
		    {
		    	quit = true;
		    }

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
                exit_now = true;
            }
        }

        //Fill screen
    	SDL_FillRect( graphics.screen, &graphics.screen->clip_rect, SDL_MapRGB( graphics.screen->format, 0x80, 0x80, 0x80 ) );

    	char msg[100] = {"Top Players"};
	    score_msg = TTF_RenderText_Solid( font, msg, text_color );
	    apply_surface( ( ( graphics.screen_width / 2 ) - ( score_msg->w / 2) ), 25, score_msg, graphics.screen, NULL );

		//show the scores
		int i;
		for( i = 0; i < 10; i++ )
		{
	        char score[100];
		    sprintf( score, "%s %d", h->scores[9-i].name, h->scores[9-i].score );

		    score_msg = TTF_RenderText_Solid( font, score, text_color );
		    apply_surface( ( graphics.screen_width - ( score_msg->w + 200) ), 35 * i + 75 , score_msg, graphics.screen, NULL );
		}

	    //Update the screen
        if( SDL_Flip( graphics.screen ) == -1 )
        {
            return 1;
        }
    }
    if( exit_now )
    {
    	return -1;
    }

    return 0;
}