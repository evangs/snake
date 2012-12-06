//The headers
#include <stdio.h>
#include <time.h>
#include "bool.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "prototypes.h"

#include "main_menu/graphics.h"
#include "main_menu/sound.h"
#include "main_menu/controls.h"

#include "highscores.h"

#include "gameglobals.h"
#include "stringinput.h"
#include "button.h"
#include "timer.h"
#include "segment.h"
#include "food.h"
#include "snake.h"
#include "game.h"
#include "main_menu/highscores_menu.h"
#include "main_menu/mainmenu.h"


SDL_Surface *load_image( char* filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0, 0 ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    graphics_set_video_mode( &graphics, 512, 512, 32 );

    //If there was an error in setting up the screen
    if( graphics.screen == NULL )
    {
        return false;
    }

    //initialize sdl_ttf
    if ( TTF_Init() == -1 )
    {
        return 1;
    }

    //initialize sdl_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return 1;
    }

    //load controls
    controls_load_keys( &controls );

    //setup sound
    sound_update( &sound, 128, 128, true );

    //Set the window caption
    SDL_WM_SetCaption( "Snake", NULL );

    //load high scores
    highscores_read_from_file( &highscores );
    //highscores_save_to_file( &highscores );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load images
    play_button = load_image( "Snake.app/Contents/Resources/play.png" );
    quit_button = load_image( "Snake.app/Contents/Resources/quit.png" );
    highscores_button = load_image( "Snake.app/Contents/Resources/highscores.png" );
    sound_button = load_image( "Snake.app/Contents/Resources/sound.png" );
    controls_button = load_image( "Snake.app/Contents/Resources/controls.png" );
    arrow = load_image( "Snake.app/Contents/Resources/arrow.png" );

    head = load_image( "Snake.app/Contents/Resources/head.png" );
    head_l = load_image( "Snake.app/Contents/Resources/head_l.png" );
    head_d = load_image( "Snake.app/Contents/Resources/head_d.png" );
    head_r = load_image( "Snake.app/Contents/Resources/head_r.png" );
    body = load_image( "Snake.app/Contents/Resources/segment.png" );
    apple = load_image( "Snake.app/Contents/Resources/apple.png" );
    donut = load_image( "Snake.app/Contents/Resources/donut.png" );

    font = TTF_OpenFont( "Snake.app/Contents/Resources/AccidentalPresidency.ttf", 24 );

    if( ( play_button == NULL ) || ( quit_button == NULL ) || ( highscores_button == NULL ) || ( sound_button == NULL ) || ( controls_button == NULL ) || ( arrow == NULL ) )
    {
        return false;
    }

    //If there was a problem in loading the images
    if( ( head == NULL ) || ( head_l == NULL ) || ( head_d == NULL ) || ( head_r == NULL ) || ( body == NULL ) || ( apple == NULL ) || ( donut == NULL ) )
    {
        return false;
    }

    //if there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    //load the music
    music = Mix_LoadMUS( "Snake.app/Contents/Resources/snake_music.wav" );

    //if there was a problem loading the music
    if( music == NULL )
    {
        return 1;
    }

    //Load the sound effects
    crunch = Mix_LoadWAV( "Snake.app/Contents/Resources/crunch.wav" );
    ouch = Mix_LoadWAV( "Snake.app/Contents/Resources/ouch.wav" );

    //If there was a problem loading the sound effects
    if( ( crunch == NULL ) || ( ouch == NULL ) )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //save high scores
    highscores_save_to_file( &highscores );

    //Free the surfaces
    SDL_FreeSurface( play_button );
    SDL_FreeSurface( highscores_button );
    SDL_FreeSurface( quit_button );
    SDL_FreeSurface( sound_button );
    SDL_FreeSurface( controls_button );
    SDL_FreeSurface( arrow );

    SDL_FreeSurface( message );

    SDL_FreeSurface( head );
    SDL_FreeSurface( body );
    SDL_FreeSurface( apple );
    SDL_FreeSurface( donut );
    SDL_FreeSurface( score_msg );

    //Free the sound effects
    Mix_FreeChunk( crunch );
    Mix_FreeChunk( ouch );

    //Free the music
    Mix_FreeMusic( music );

    //close the font
    TTF_CloseFont( font );

    //Quit SDL_mixer
    Mix_CloseAudio();

    //quit sdl_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //seed random with time
    srand(time(0));

    bool quit = false;
    int gameOver = -1;
    
    
    //Initialize
    if( !init() )
    {
        printf( "init failed\n" );
        return 1;
    }

    //Load the files
    if( !load_files() )
    {
        printf( "load failed\n" );
        return 1;
    }

    
    int status = 0;
    

    //Fill screen
    SDL_FillRect( graphics.screen, &graphics.screen->clip_rect, SDL_MapRGB( graphics.screen->format, 0x80, 0x80, 0x80 ) );

    //While the user hasn't quit
    while( quit == false )
    {
        Mainmenu mm;
        mainmenu_init( &mm );
        status = mainmenu_play( &mm );
        if( status == -1 )
        {
            break;
        }

        //While there's event to handle
        while( SDL_PollEvent( &event ) )
        {

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }


        //Update the screen
        if( SDL_Flip( graphics.screen ) == -1 )
        {
            return 1;
        }
    }

    //Clean up
    clean_up();

    return 0;   //no errors
}
