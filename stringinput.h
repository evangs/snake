//stringinput.h

//The stringinput
typedef struct
{
    //the storage string
    char str[25];

    //the length of the string
    int length;

    //the text surface
    SDL_Surface *text;

}StringInput;

void StringInputInit( StringInput * si )
{
	//initialize the length
	si->length = 0;

	int i;
	for( i = 0; i < 25; i++ )
	{
		si->str[i] = '\0';
	}

	//initialize the surface
	si->text = NULL;

	//enable unicode
	SDL_EnableUNICODE( SDL_ENABLE );
}

void StringInputDel( StringInput * si )
{
	//free text surface
	SDL_FreeSurface( si->text );

	//disable unicode
	SDL_EnableUNICODE( SDL_DISABLE );
}

void StringInputHandleInput( StringInput * si )
{
	//If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Keep a copy of the current version of the string
        int i;
        char temp[25];
        for( i = 0; i < 25; i++ )
        {
        	temp[i] = si->str[i];
        }

        //If the string less than maximum size
        if( si->length <= 25 )
        {
            //If the key is a space
            if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
            {
                //Append the character
                si->str[si->length] = (char)event.key.keysym.unicode;
                si->length++;
            }
            //If the key is a uppercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
            {
                //Append the character
                si->str[si->length] = (char)event.key.keysym.unicode;
                si->length++;
            }
            //If the key is a lowercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
            {
                //Append the character
                si->str[si->length] = (char)event.key.keysym.unicode;
                si->length++;
            }
        }

        //If backspace was pressed and the string isn't blank
        if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( si->length != 0 ) )
        {
            //Remove a character from the end
            si->str[si->length - 1] = '\0';
            si->length--;
        }

        //If the string was changed
        if( si->str != temp )
        {
            //Free the old surface
            SDL_FreeSurface( si->text );

            //Render a new text surface
            si->text = TTF_RenderText_Solid( font, si->str, text_color );
        }
    }
}

void StringInputShowCentered( StringInput * si )
{
	//If the surface isn't blank
    if( si->text != NULL )
    {
        //Show the name
        apply_surface( ( graphics.screen_width - si->text->w ) / 2, ( graphics.screen_height - si->text->h ) / 2, si->text, graphics.screen, NULL );
    }
}