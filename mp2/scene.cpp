# include "scene.h"
# include <iostream>
# include "image.h"
# include "rgbapixel.h"
# include <cstdint>
using namespace std;

Scene :: Scene (int max){

    scene1 = new Image*[max];
    xcoords1 = new int[max];
    ycoords1 = new int[max];
    for (int i=0; i < max; i++){
	scene1[i] = NULL;
	xcoords1[i] = 0;
	ycoords1[i] = 0;
    }
    this -> maxSize = max;
}

Scene :: ~ Scene(){
    clear();
}



Scene :: Scene (const Scene &source){
    copy(source);
}

const Scene & Scene :: operator= (const Scene &source){
    if (this != &source){
	clear();
	copy(source);
    }    
    return *this;
}

void Scene :: changemaxlayers (int newmax){
    for (int i = newmax-1; i < maxSize; i++){
	if (scene1[i] != NULL){
	    cout << "invalid newmax" << endl;
	    return;
	}
    }
    
    if (maxSize == newmax){
	return;
    }

    Image** scene2 = new Image*[newmax];
    int* xcoord2 = new int[newmax];
    int* ycoord2 = new int[newmax];

    for (int i = 0; i < newmax; i++){
	if (i >= maxSize){
	    scene2[i] = NULL;
	}
	else{
	    scene2[i] = scene1[i];
	    xcoord2[i] = xcoords1[i];
	    ycoord2[i] = ycoords1[i];
	}
    }
    clear();
    scene1 = scene2;
    xcoords1 = xcoord2;
    ycoords1 = ycoord2;
    maxSize = newmax;
}

void Scene :: addpicture (const char *FileName, int index, int x, int y){
    if (index >= 0 && index < maxSize) {
	input = new Image;
	input -> readFromFile(FileName);
	scene1[index] = input;
	xcoords1[index] = x;
	ycoords1[index] = y;
    }
    else
	cout << "index out of bounds" << endl;
}
	

void Scene :: changelayer (int index, int newindex){
    if (index >= 0 && index < maxSize && newindex >= 0 && newindex < maxSize){
        if (newindex != index){
	    if (scene1[newindex] != NULL){
	        delete scene1[newindex];
		scene1[newindex] = NULL;
	    }

	    scene1[newindex] = scene1[index];
	    xcoords1[newindex] = xcoords1[index];
	    ycoords1[newindex] = ycoords1[index];
	    scene1[index] = NULL;

	}
    }
    else
	cout << "invalid index" << endl;
}

void Scene :: translate (int index, int xcoord, int ycoord){
    if (index >= 0 && index < maxSize && scene1[index] != NULL){
	xcoords1[index] = xcoord;
	ycoords1[index] = ycoord;
    }
    else
	cout << "invalid index" << endl;
}

void Scene :: deletepicture (int index){
    if (index >= 0 && index < maxSize && scene1[index] != NULL){
	delete scene1[index];
	scene1[index] = NULL;
    }
    else
	cout << "invalid index" << endl; 
}

Image* Scene :: getpicture (int index) const{
    if (index >= 0 && index < maxSize){
	return scene1[index];
    }
    else{
	cout << "invalid index" << endl;
	return NULL;
    }
}

Image Scene :: drawscene() const{

    size_t w = 0;
    size_t h = 0;

    size_t layerw = 0;
    size_t layerh = 0;
    // determine the size of the scene
    for (int i = 0; i < maxSize; i++){
	if (scene1[i] != NULL){
	    layerw = scene1[i] -> width() + (size_t)xcoords1[i];
	    layerh = scene1[i] -> height() + (size_t)ycoords1[i];
	    if (layerw > w)
	        w = layerw;
	    if (layerh > h)
	        h = layerh;
	}
    }

    Image output(w,h);
    RGBAPixel* ptr;
    for (int i = 0; i < maxSize; i++){

	if (scene1[i] != NULL){
	    size_t tmpw = scene1[i] -> width();
	    size_t tmph = scene1[i] -> height();
	    size_t xcoord = size_t(xcoords1[i]);
	    size_t ycoord = size_t(ycoords1[i]);
	    for(size_t j = 0; j < tmpw; j++){
		for(size_t k = 0; k < tmph; k++){    
		    ptr = output(size_t(xcoord + j), size_t(ycoord + k));
   		    *ptr = *((*scene1[i])(j,k));
		    
  		}
	    }
	}
    }
    return output;
}
	

void Scene :: copy (const Scene &source){
    maxSize = source.maxSize;
    xcoords1 = new int[maxSize];
    ycoords1 = new int[maxSize];
    scene1 = new Image*[maxSize];

    // initialize
    for (int i=0; i< maxSize; i++){
	scene1[i] = NULL;
	xcoords1[i] = 0;
	ycoords1[i] = 0;
    }

    // copy
    for (int i=0; i < maxSize; i++){
	if (source.scene1[i] != NULL){
	    scene1[i] = new Image;
	    *scene1[i] = *(source.scene1[i]);
	    xcoords1[i] = source.xcoords1[i];
	    ycoords1[i] = source.ycoords1[i];
	}
    }
}

void Scene :: clear(){
    for (int i = 0; i < maxSize; i++){
	if (scene1[i] != NULL){
	    delete scene1[i];
	    scene1[i] = NULL;
	}
    }
    delete [] scene1;
    scene1 = NULL;
    if (xcoords1 != NULL){
        delete [] xcoords1;
        xcoords1 = NULL;
    }
    if (ycoords1 != NULL){
        delete [] ycoords1;
        ycoords1 = NULL;
    }
}



    
