#include"image.h"
#include"rgbapixel.h"

void Image::flipleft(){
	RGBAPixel *tmp = new RGBAPixel;
	size_t w = this -> width();
	size_t h = this -> height();

	for(size_t x = 0; x < w/2; x++){
		for(size_t y = 0; y < h; y++){
			*tmp = *(*this)(x,y);
			*(*this)(x,y) = *(*this)(w-1-x,y);
			*(*this)(w-1-x,y) = *tmp;
		}
	}
	
	delete tmp;
}

void Image::adjustbrightness(int r, int g, int b){
	size_t w = this -> width();
	size_t h = this -> height();
	
	int test = 0;
	for(size_t x = 0; x < w; x++){
		for(size_t y = 0; y < h; y++){
			// do the red pixel
			test = (*this)(x,y) -> red + r;
			if (test > 255)
				(*this)(x,y) -> red = 255;
			else if (test < 0)
				(*this)(x,y) -> red = 0;
			else 
				(*this)(x,y) -> red = test;
			
			// do the green pixel
			test = (*this)(x,y)-> green + g;
			if (test > 255)
				(*this)(x,y) -> green = 255;
			else if (test < 0)
				(*this)(x,y) -> green = 0;
			else 
				(*this)(x,y) -> green = test;
			
			// do the blue pixel
			test = (*this)(x,y) -> blue + b;
			if (test > 255)
				(*this)(x,y) -> blue = 255;
			else if (test < 0)
				(*this)(x,y) -> blue = 0;
			else 
				(*this)(x,y) -> blue = test;

		}
	}
}

void Image::invertcolors(){
	size_t w = this -> width();
	size_t h = this -> height();
	
	for(size_t x = 0; x < w; x++){
		for(size_t y = 0; y < h; y++){
			(*this)(x,y) -> red = 255 - (*this)(x,y) -> red;
			(*this)(x,y) -> green = 255 - (*this)(x,y) -> green;
			(*this)(x,y) -> blue = 255 - (*this)(x,y) -> blue;
		}
	}
}

	
	
		
			
	


	
