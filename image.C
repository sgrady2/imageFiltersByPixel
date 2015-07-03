//This is going to hold methods for the Image class
#include <stdio.h>
#include <stdlib.h>
#include <image.h>
#include <source.h>
void Image::setSource(Source *srce)
{
	src = srce;
}
void Image::Update() const
{
	if (src != NULL){
	src->Update();	
	}
}
void Image::ResetSize(int w, int h)
{
	//reset the image by mallocing a new array in its place
	width = w;
	height = h;
	//Valgrind was freaking out about my calls in ResetSize
	//when I saw the below call it only makes sense that every
	//time this is called i need to free my currently used memory
	//before mallocing new memory or my program will have a leak
	data = new unsigned char[3*width*height];
}

unsigned char * Image::readPixel(int w, int h)const
{	
	// returns a pointer to the current pixel at width w and height h
	// of my images buffer

	int i = h*width+w;
	return data+3*i;
}
void Image::writePixel(int w, int h, unsigned char *p)const
{
	//now write to each color channel of data using an index and the read pixel array passed 
	//and + 0, 1, 2 to move through the unsigned char array 
	
	int i = h*width+w;
	data[3*i+0] = p[0];
	data[3*i+1] = p[1];
	data[3*i+2] = p[2];


}
//switched over all of my inline declarations, so much neater XD

Image::~Image(){
	if (data != NULL){
	delete [] data;
	}
}
Image::Image(int w, int h) 
 {
             width = w;
             height = h;
             data = new unsigned char[3*w*h];
 }
Image::Image(void)
{
             int width = 0;
             int height = 0;
	     src= NULL;
}
Image::Image(Image &img)
{
      width = img.width;
      height = img.height;
      data = img.data;
}
