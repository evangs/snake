/*
graphics.h

represents game graphics and stores user preferences

author: Evan Sailer, 11/9/2012

Graphics
	int screen_width
	int screen_height
	int screen_bpp
*/

typedef struct
{
	//screen width
    int screen_width;

 	//screen height
	int screen_height;

	//screen bits per pixel
	int screen_bpp;

	SDL_Surface *screen;

}Graphics;

void graphics_set_video_mode( Graphics * g, int screen_width, int screen_height, int screen_bpp )
{
	//set graphics variables
	g->screen_width = screen_width;
	g->screen_height = screen_height;
	g->screen_bpp = screen_bpp;

	//Set up the screen
    g->screen = SDL_SetVideoMode( g->screen_width, g->screen_height, g->screen_bpp, SDL_SWSURFACE );
}

void graphics_save_video_config( Graphics * g )
{
	//writes current video configuration to video.cfg overwriting anything currently in the file
    FILE *fp;
    fp = fopen( "video.cfg", "w+" );

    //write keys to file
    fprintf( fp, "%d %d %d", g->screen_width, g->screen_height, g->screen_bpp );

    fclose( fp );
}

void graphics_load_video_config( Graphics * g )
{
	//loads video settings from video.cfg.  if error with load sets graphics to defaults
    FILE *fp;
    fp = fopen( "video.cfg", "r" );

    if( fp != NULL )
    {
        //the keys
        int w, h, b;

        //set the keys
        fscanf( fp, "%d %d %d", &w, &h, &b );

        //make sure video settings are valid

        g->screen_width = w;
        g->screen_height = h;
        g->screen_bpp = b;

        fclose( fp );
    }
    else
    {
    	g->screen_width = 640;
        g->screen_height = 480;
        g->screen_bpp = 32;
    }

    //Set up the screen
    g->screen = SDL_SetVideoMode( g->screen_width, g->screen_height, g->screen_bpp, SDL_SWSURFACE );
}