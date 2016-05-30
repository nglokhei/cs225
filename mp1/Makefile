EXENAME = mp1
OBJS = main.o png.o rgbapixel.o

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all: $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)				
main.o: main.cpp rgbapixel.h png.h
	$(CXX) $(CXXFLAGS) main.cpp
rgbapixel.o: rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp
png.o: png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp
clean:
	-rm -f *.o $(EXENAME)

