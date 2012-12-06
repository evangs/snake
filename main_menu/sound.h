/*
sound.h

represents game sound and stores user preferences

author: Evan Sailer, 11/10/2012

Sound
	int music_volume
	int sfx_volume
	bool bg_music
*/

typedef struct
{
	//background music volume
    int music_volume;

 	//sound effects volume
	int sfx_volume;

	//turns background music on or off
	bool bg_music;

}Sound;

void sound_update( Sound * s, int m_vol, int s_vol, bool bg )
{
	s->music_volume = m_vol;
	s->sfx_volume = s_vol;
	s->bg_music = bg;

	Mix_VolumeMusic( s->music_volume );
	Mix_Volume( -1, s->sfx_volume );
}

void sound_save_config( Sound * s )
{
	//writes current sound configuration to sound.cfg overwriting anything currently in the file
    FILE *fp;
    fp = fopen( "sound.cfg", "w+" );

    //write keys to file
    fprintf( fp, "%d %d %d", s->music_volume, s->sfx_volume, s->bg_music );

    fclose( fp );
}

void sound_load_config( Sound * s ) 
{
	//loads sound config from sound.cfg.  if error with load sets sound to defaults
    FILE *fp;
    fp = fopen( "sound.cfg", "r" );

    if( fp != NULL )
    {
        //the keys
        int mv, sv, bg;

        //set the keys
        fscanf( fp, "%d %d %d", &mv, &sv, &bg );

        //make sure sound settings are valid

        s->music_volume = mv;
        s->sfx_volume = sv;
        s->bg_music = bg;

        fclose( fp );
    }
    else
    {
    	s->music_volume = 128;
        s->sfx_volume = 128;
        s->bg_music = true;
    }
}