# from http://stackoverflow.com/questions/5088460/flags-to-enable-thorough-and-verbose-g-warnings/9862800#9862800
# list from post :
INITIAL = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization \
            -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs \
            -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
            -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wzero-as-null-pointer-constant

# present on the post but not wanted :
# -Wnoexcept -Wno-unused -Werror
# extra from the post (but initially excluded) :
# still not wanted :
# -Wsuggest-attribute -Wno-long-long -Waggregate-return -Wpadded
# wanted :
WARNINGS = ${INITIAL} -Wabi -Wconversion -Weffc++ -Winline -Winvalid-pch -Wnormalized=nfc \
                      -Wstack-protector -Wstrict-aliasing=1 -Wswitch-enum -Wunsafe-loop-optimizations -Wmissing-format-attribute
# GCC 4.8 : -Wuseless-cast -Wpedantic (-pedantic deprecated)

# easy :
#WARNINGS = -Wall -Wextra -Weffc++ -pedantic

STD = -std=c++11

LIBRARIES = `sdl-config --cflags --libs` `wx-config --cxxflags --libs` -lSDL_image -lSDL_gfx -lSDL_ttf -lSDL

CPPFLAGS = ${STD} ${WARNINGS} ${LIBRARIES}
APPNAME = ATCsim

all:
	g++ *.cpp ${CPPFLAGS} -o ${APPNAME}

clean:
	rm -f ${APPNAME} *~

