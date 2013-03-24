CFLAGS = -Wall `sdl-config --cflags --libs` `wx-config --cxxflags --libs` -lSDL_image -lSDL_gfx -lSDL_ttf -lSDL
APPNAME = ATCsim

all:
	g++ *.cpp ${CFLAGS} -o ${APPNAME}

clean:
	rm -f ${APPNAME} *~
