EXENAME1 = testimage
OBJS1 = testimage.o image.o png.o rgbapixel.o
EXENAME2 = testscene
OBJS2 = testscene.o scene.o image.o rgbapixel.o png.o

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all: $(EXENAME1) $(EXENAME2)

$(EXENAME1): $(OBJS1)
	$(LD) $(OBJS1) $(LDFLAGS) -o $(EXENAME1)
$(EXENAME2): $(OBJS2)
	$(LD) $(OBJS2) $(LDFLAGS) -o $(EXENAME2)
testimage.o: testimage.cpp image.h 
	$(CXX) $(CXXFLAGS) testimage.cpp
testscene.o: testscene.cpp image.h scene.h png.h
	$(CXX) $(CXXFLAGS) testscene.cpp
rgbapixel.o: rgbapixel.cpp rgbapixel.h 
	$(CXX) $(CXXFLAGS) rgbapixel.cpp
png.o: png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp
image.o: image.cpp image.h
	$(CXX) $(CXXFLAGS) image.cpp
scene.o: scene.cpp scene.h image.h rgbapixel.h
	$(CXX) $(CXXFLAGS) scene.cpp
clean:
	rm -f *.o $(EXENAME1)
	rm -f *.o $(EXENAME2)
