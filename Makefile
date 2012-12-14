# Makefile to build the SDL tests

srcdir  = .

CC      = gcc
EXE	= 
CFLAGS  = -g -O2 -I/usr/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -DHAVE_OPENGL
LIBS	= -L/usr/local/lib -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -Wl,-framework,Cocoa
#LIBS    = -lz -L/usr/local/lib /usr/local/lib/libSDLmain.a /usr/local/lib/libSDL.a /usr/local/lib/libSDL_image.a /usr/local/lib/libSDL_mixer.a /usr/local/lib/libSDL_ttf.a /usr/local/lib/libfreetype.a /usr/local/lib/libpng.a /usr/local/lib/libbz2.a -Wl,-framework,OpenGL -Wl,-framework,Cocoa -Wl,-framework,ApplicationServices -Wl,-framework,Carbon -Wl,-framework,AudioToolbox -Wl,-framework,AudioUnit -Wl,-framework,IOKit

main: $(srcdir)/main.c
	$(CC) -o $@ $? $(CFLAGS) $(LIBS)

Snake: $(srcdir)/main.c
	$(CC) -o $@ $? $(CFLAGS) $(LIBS)

clean:
	rm -f main
	rm -f Snake


