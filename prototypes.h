//prototypes.h
void apply_surface( int, int, SDL_Surface*, SDL_Surface*, SDL_Rect* );
Uint32 get_pixel32( int x, int y, SDL_Surface *surface )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Get the pixel requested
    return pixels[ ( y * surface->w ) + x ];
}