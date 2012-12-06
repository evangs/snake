//Button.h

//The button
typedef struct
{
    //The attributes of the button
    SDL_Rect box;

    //The part of the button sprite sheet that will be shown
    bool active;
    bool clicked;

}Button;

void ButtonInit( Button * b, int x, int y, int w, int h )
{
	if (b == NULL)
		return;
    //Set the button's attributes
    b->box.x = x;
    b->box.y = y;
    b->box.w = w;
    b->box.h = h;

    //Set the default sprite
    b->active = false;
    b->clicked = false;
}

void ButtonHandleEvents( Button * b )
{
    //The mouse offsets
    int x = 0, y = 0;

    //if the mouse is over the button
    if( event.type == SDL_MOUSEMOTION )
    {
        //Get the mouse offsets
        x = event.motion.x;
        y = event.motion.y;

        //If the mouse is over the button
        if( ( x > b->box.x ) && ( x < b->box.x + b->box.w ) && ( y > b->box.y ) && ( y < b->box.y + b->box.h ) )
        {
            //Set the button active
            b->active = true;
        }
        //If not
        else
        {
            //Set the button not active
            b->active = false;
        }
    }    
    //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > b->box.x ) && ( x < b->box.x + b->box.w ) && ( y > b->box.y ) && ( y < b->box.y + b->box.h ) )
            {
                //Set the button sprite
                b->clicked = true;
            }
        }
    }
    //If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP )
    {
        //If the left mouse button was released
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > b->box.x ) && ( x < b->box.x + b->box.w ) && ( y > b->box.y ) && ( y < b->box.y + b->box.h ) )
            {
                //Set the button sprite
                b->clicked = false;
            }
        }
    }
}

void ButtonShow(Button * b, SDL_Surface *button, SDL_Surface *buttonActive)
{
    //Show the button
    if( b->clicked )
    {
        apply_surface( b->box.x, b->box.y, buttonActive, graphics.screen, NULL );
    }
    else
    {
        apply_surface( b->box.x, b->box.y, button, graphics.screen, NULL );
    }
}