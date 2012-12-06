/* File timer.h  */
#ifndef FILE_TIMER_SEEN
#define FILE_TIMER_SEEN

//The Timer
typedef struct
{
    //The clock time when the timer started
    int startTicks;
    
    //The ticks stored when the timer was paused
    int pausedTicks;
    
    //The timer status
    int paused;
    int started;

}Timer;

//Initializes variables
void TimerInit( Timer * t )
{
    //Initialize the variables
    t->startTicks = 0;
    t->pausedTicks = 0;
    t->paused = 1;
    t->started = 1;  
}

//The various clock actions
void TimerStart( Timer * t )
{
    //Start the timer
    t->started = 0;
    
    //Unpause the timer
    t->paused = 1;
    
    //Get the current clock time
    t->startTicks = SDL_GetTicks(); 
}
void TimerStop( Timer * t )
{
    //Stop the timer
    t->started = 1;
    
    //Unpause the timer
    t->paused = 1;  
}
void TimerPause( Timer * t )
{
    //If the timer is running and isn't already paused
    if( ( t->started == 0 ) && ( t->paused == 1 ) )
    {
        //Pause the timer
        t->paused = 0;
    
        //Calculate the paused ticks
        t->pausedTicks = SDL_GetTicks() - t->startTicks;
    }
}
void TimerUnpause( Timer * t )
{
    //If the timer is paused
    if( t->paused == 0 )
    {
        //Unpause the timer
        t->paused = 1;
    
        //Reset the starting ticks
        t->startTicks = SDL_GetTicks() - t->pausedTicks;
        
        //Reset the paused ticks
        t->pausedTicks = 0;
    }
}

//Gets the timer's time
int TimerGetTicks( Timer * t )
{
    //If the timer is running
    if( t->started == 0 )
    {
        //If the timer is paused
        if( t->paused == 0 )
        {
            //Return the number of ticks when the timer was paused
            return t->pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - t->startTicks;
        }    
    }
    
    //If the timer isn't running
    return 0;
}

//Checks the status of the timer
int TimerIsStarted( Timer * t )
{
    return t->started;
}
int TimerIsPaused( Timer * t )
{
    return t->paused;
}

#endif /* !FILE_TIMER_SEEN */