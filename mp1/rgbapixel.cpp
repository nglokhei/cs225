#include "rgbapixel.h"

RGBAPixel::RGBAPixel(){
	alpha = 255;
	red = 255;
	green = 255;
	blue = 255;
}

RGBAPixel::RGBAPixel(uint8_t red, uint8_t green, uint8_t blue){
	alpha= 255;
	this->red = red;
	this->blue = blue;
	this->green = green;
}


