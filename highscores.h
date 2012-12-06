/*
highscores.h
some useful functions to make keeping track of high scores easy.

Highscores
	Highscore[] scores
		int score
		char* name
	save_to_file()
	read_from_file()
	add_highscore()
*/

typedef struct
{
    //the score
    int score;

    //players name
    char name[25];

}Highscore;

typedef struct
{
    //the high scores
    Highscore scores[10];

}Highscores;

highscores_save_to_file( Highscores * h )
{
	//writes current highscores to highscores.dat overwriting anything currently in the file
    FILE *fp;
    fp = fopen( "highscores.dat", "w+" );

    //write scores to file
    int i;
    for( i = 0; i < 10; i++ )
    {
    	fprintf( fp, "%s %d\n", h->scores[i].name, h->scores[i].score );
	}

    fclose( fp );
}

highscores_read_from_file( Highscores * h )
{
	//loads highscors from highscores.dat.  if error with load sets highscores to defaults
    FILE *fp;
    fp = fopen( "highscores.dat", "r" );

    if( fp != NULL )
    {
        //set the score
        int i;
        for( i = 0; i < 10; i++ )
        {
        	int s;
        	char n[25];

        	fscanf( fp, "%s %d\n", n, &s );
        	strcpy( h->scores[i].name, n );
        	h->scores[i].score = s;
        }

        //make sure sound settings are valid

        fclose( fp );
    }
    else
    {
    	int i;
    	for( i = 0; i < 10; i++ )
    	{
    		strcpy( h->scores[i].name, "EHoM" );
    		h->scores[i].score = i * 10;
    	}
    }
}

highscores_add_score( Highscores * h, Highscore hs )
{
	int index = -1;
	int i;
	for( i = 0; i < 10; i++ )
	{
		if( hs.score > h->scores[i].score )
		{
			index = i;
		}
		else
		{
			break;
		}
	}

	if( index > -1 )
	{
		//shift all lower scores
		for( i = 0; i < index; i++ )
		{
			h->scores[i] = h->scores[i+1];
		}
		h->scores[index] = hs;
	}
	highscores_save_to_file( h );
}