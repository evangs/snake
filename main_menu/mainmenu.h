/*
mainmenu.h

represents game main menu with all buttons and controls

author: Evan Sailer, 11/9/2012

Mainmenu
	Button b1
	Button b2
	Slider s1

	init()
	handle_input()
	show()
*/

typedef struct
{
	//play button
	Button play;

	//view high score button
	Button highscore;

	//controls button
	Button controls;

	//sound button
	Button sound;

	//quit button
	Button quit;

	//arrow position
	SDL_Rect arrow;

}Mainmenu;

void mainmenu_init( Mainmenu * m )
{
	ButtonInit( &m->play, 64, 0, 256, 64 );
	ButtonInit( &m->highscore, 64, 64, 256, 64 );
	ButtonInit( &m->controls, 64, 128, 256, 64 );
	ButtonInit( &m->sound, 64, 192, 256, 64 );
	ButtonInit( &m->quit, 64, 256, 256, 64 );

	m->arrow.x = 0;
	m->arrow.y = 0;
}

void mainmenu_handle_input( Mainmenu * m )
{
	ButtonHandleEvents( &m->play );
	ButtonHandleEvents( &m->highscore );
	ButtonHandleEvents( &m->controls );
	ButtonHandleEvents( &m->sound );
	ButtonHandleEvents( &m->quit );

	if( m->play.active )
	{
		m->arrow.y = m->play.box.y;
	}
	else if( m->highscore.active )
	{
		m->arrow.y = m->highscore.box.y;
	}
	else if( m->controls.active )
	{
		m->arrow.y = m->controls.box.y;
	}
	else if( m->sound.active )
	{
		m->arrow.y = m->sound.box.y;
	}
	else if( m->quit.active )
	{
		m->arrow.y = m->quit.box.y;
	}
}

void mainmenu_show( Mainmenu * m )
{
    ButtonShow( &m->play, play_button, play_button );
    ButtonShow( &m->highscore, highscores_button, highscores_button );
    ButtonShow( &m->controls, controls_button, controls_button );
    ButtonShow( &m->sound, sound_button, sound_button );
    ButtonShow( &m->quit, quit_button, quit_button );

    apply_surface( m->arrow.x, m->arrow.y, arrow, graphics.screen, NULL );
}

int mainmenu_play( Mainmenu * m )
{
	Game theGame;
	int game_ret;
	bool quit = false;

	//Play the music
    if ( sound.bg_music )
    {
    	if( !Mix_PlayingMusic() )
    	{
		    if( Mix_PlayMusic( music, -1 ) == -1 )
		    {
		        return 1;
		    }
		}
	}

	while( !quit )
	{
		//While there's event to handle
        while( SDL_PollEvent( &event ) )
        {
        	mainmenu_handle_input( m );

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
        //Fill screen
   	 	SDL_FillRect( graphics.screen, &graphics.screen->clip_rect, SDL_MapRGB( graphics.screen->format, 0x80, 0x80, 0x80 ) );

        mainmenu_show( m );

        //Update the screen
        if( SDL_Flip( graphics.screen ) == -1 )
        {
            return 1;
        }

        if( m->play.clicked )
        {
        	GameInit( &theGame );
        	game_ret = GamePlay( &theGame );
        	return game_ret;
        }
        else if( m->highscore.clicked )
        {
        	return highscores_show( &highscores );
        	//printf( "highscore clicked\n" );
        }
        else if( m->controls.clicked )
        {
        	printf( "controls clicked\n" );
        }
        else if( m->sound.clicked )
        {
        	printf( "sound clicked\n" );
        }
        else if( m->quit.clicked )
        {
        	return -1;
        }
	}
	return -1;
}