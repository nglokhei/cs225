#include<iostream>
#include"png.h"
#include"rgbapixel.h"
using namespace::std;

int main(){
	//setup variables
	PNG input("in.png");
	size_t h = input.height();
	size_t w = input.width();
	PNG output(w,h);
	
	//rotate image
	for(size_t x = 0;x < w; x++){
		for(size_t y = 0;y < h; y++){
			output(x,y)->red = input(w-x-1,h-y-1)->red;
			output(x,y)->green = input(w-x-1,h-y-1)->green;
			output(x,y)->blue = input(w-x-1,h-y-1)->blue;
			output(x,y)->alpha = input(w-x-1,h-y-1)->alpha;
		}
	}

	//write output
	output.writeToFile("out.png");


	return 0;

}
	
