# from http://stackoverflow.com/questions/5088460/flags-to-enable-thorough-and-verbose-g-warnings/9862800#9862800
# list from post :
INITIALWARN = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization \
              -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept \
              -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
              -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wzero-as-null-pointer-constant

# present on the post but not wanted :
# -Wno-unused -Werror
# extra from the post (but initially excluded) :
# still not wanted :
# -Wsuggest-attribute -Wno-long-long -Waggregate-return
# wanted :
WARNINGS = ${INITIALWARN} -Wabi -Wconversion -Weffc++ -Winline -Winvalid-pch -Wnormalized=nfc -Wstack-protector \
                          -Wstrict-aliasing=1 -Wswitch-enum -Wunsafe-loop-optimizations -Wmissing-format-attribute -Wpadded
# GCC 4.8 : -Wuseless-cast -Wpedantic (-pedantic deprecated)

# easy :
#WARNINGS = -Wall -Wextra -Weffc++ -pedantic

# To be inspected times to times (noisy) :
NONOISYWARNINGS = -Wno-unused-parameter -Wno-padded



STD = -std=c++11

#LIBRARIES = `sdl-config --cflags --libs` `wx-config --cxxflags --libs` -lSDL_image -lSDL_gfx -lSDL_ttf
LIBRARIES = `sdl-config --cflags --libs` -lSDL_gfx -lSDL_ttf

APPNAME = ATCsim



.gcc:
	g++ *.cpp ${LIBRARIES} ${STD} ${WARNINGS} ${NONOISYWARNINGS} -O2 -o ${APPNAME}_gcc

.clang:
	clang++ *.cpp ${LIBRARIES} ${STD} -Weverything ${NONOISYWARNINGS} -O2 -o ${APPNAME}_clang

default:
	g++ *.cpp ${LIBRARIES} ${STD} -O2 -o ${APPNAME}_gcc

all: .gcc .clang
gcc: .gcc
clang: .clang

clean:
	rm -f ${APPNAME}* *~

