/*
gameglobals.h
global variables used in the game
*/

//Screen attributes
Graphics graphics;

//The frames per second
int FRAMES_PER_SECOND = 5;
int MAX_FRAMES_PER_SECOND = 60;

//segment width and height
#define SEGMENT_WIDTH 16
#define SEGMENT_HEIGHT 16

//snake directions
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

//food types
#define APPLE 0
#define DONUT 1

//The surfaces
SDL_Surface *play_button = NULL;
SDL_Surface *highscores_button = NULL;
SDL_Surface *quit_button = NULL;
SDL_Surface *sound_button = NULL;
SDL_Surface *controls_button = NULL;
SDL_Surface *arrow = NULL;

SDL_Surface *message = NULL;

SDL_Surface *head = NULL;
SDL_Surface *head_l = NULL;
SDL_Surface *head_d = NULL;
SDL_Surface *head_r = NULL;
SDL_Surface *body = NULL;
SDL_Surface *apple = NULL;
SDL_Surface *donut = NULL;
SDL_Surface *score_msg = NULL;

//the font
TTF_Font *font = NULL;

//the color of the font
SDL_Color text_color = { 25, 25, 25 };

//The music that will be played
Mix_Music *music = NULL;

//The sound effects that will be used
Mix_Chunk *crunch = NULL;
Mix_Chunk *ouch = NULL;

//game controls
Controls controls;

//game sound
Sound sound;

//The event structure
SDL_Event event;

//the high scores 
Highscores highscores;