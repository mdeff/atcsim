# from http://stackoverflow.com/questions/5088460/flags-to-enable-thorough-and-verbose-g-warnings/9862800#9862800
# WARNINGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused

WARNINGS = -Wall -Wextra -Weffc++
# GCC 4.8 : -pedantic deprecated, use -Wpedantic
STD = -std=c++11 -pedantic

LIBRARIES = `sdl-config --cflags --libs` `wx-config --cxxflags --libs` -lSDL_image -lSDL_gfx -lSDL_ttf -lSDL

CPPFLAGS = ${STD} ${WARNINGS} ${LIBRARIES}
APPNAME = ATCsim

all:
	g++ *.cpp ${CPPFLAGS} -o ${APPNAME}

clean:
	rm -f ${APPNAME} *~
