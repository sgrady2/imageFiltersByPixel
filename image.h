//This is going to include data members for the Image class


#ifndef IMAGE_H
#define IMAGE_H
//#include <source.h>
#include <stdio.h>
#include <stdlib.h>


class Source;

class Image {
	private:
	    int width;
	    int height;
	    unsigned char *data;
	public:
	    void setSource(Source *srce);	    
	    Source *src;
	    void Update()const;
	    int getHeight () const
		{
			return height;
		}
	    int getWidth()const
		{
			return width;
		}
	    unsigned char * getBuffer()const
		{
			return data;
		}
	    void ResetSize(int width, int height);

	    //parameterized constructor
	    Image(int w, int h);
	    //default constructor
	    Image(void);
	    //copy constructor
	    Image(Image &img);
	    //possibly need a destructor
	    virtual ~Image();
	    void writePixel(int w, int h, unsigned char *)const;
	    unsigned char * readPixel(int w, int h)const;
};
#endif
