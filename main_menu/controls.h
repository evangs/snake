/*
controls.h

represents game controls and stores user redefinition

author: Evan Sailer, 11/7/2012

Controls
	SDLKey up
	SDLKey down
	SDLKey left
	SDLKey right

	load_keys()
	save_keys()
	set_key()
*/

typedef struct
{
    //up key
    int up;

    //down key
    int down;

    //right key
    int right;

    //left key
    int left;

    //pause key;
    int pause;

}Controls;

void controls_set_key( int * key, int new_key )
{
	*key = new_key;
}

void controls_save_keys( Controls * c )
{
	//writes current key configuration to controls.cfg overwriting anything currently in the file
    FILE *fp;
    fp = fopen( "controls.cfg", "w+" );

    //write keys to file
    fprintf( fp, "%d %d %d %d %d", c->up, c->down, c->left, c->right, c->pause );

    fclose( fp );
}

void controls_load_keys( Controls * c )
{
	//loads keys from controls.cfg.  if error with load sets keys to defaults
    FILE *fp;
    fp = fopen( "controls.cfg", "r" );

    if( fp != NULL )
    {
        //the keys
        int u, d, l, r, p;

        //set the keys
        fscanf( fp, "%d %d %d %d %d", &u, &d, &l, &r, &p );

        //make sure keys are valid

        c->up = u;
        c->down = d;
        c->left = l;
        c->right = r;
        c->pause = p;

        fclose( fp );
    }
    else
    {
    	c->up = SDLK_UP;
        c->down = SDLK_DOWN;
        c->left = SDLK_LEFT;
        c->right = SDLK_RIGHT;
        c->pause = SDLK_ESCAPE;
    }
}