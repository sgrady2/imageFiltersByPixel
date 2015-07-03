#include <sink.h>
#include <source.h>
#include <filter.h>
#include <logging.h>
#ifndef FILTERS_H
#define FILTERS_H

class Filters: public Filter{

	public:
	    virtual void Execute(){};
	    virtual const char *FilterName(){return "Filters";}

};
class TBConcat: public Filters
{
        public:
	    void Execute();
	    const char *FilterName(){return "TBConcat";};

};
class LRConcat: public Filters
{
        public:
	    void Execute();
	    const char *FilterName(){return "LRConcat";};

};

class Blender: public Filters
{
        public:
	    void SetFactor(float f){bf = f;};
	    void Execute();
	    const char *FilterName(){return "Blender";};
	
	protected:
	   float bf;

};

class Shrinker: public Filters
{
        public:
	    void Execute();
	    const char *FilterName(){return "Shrinker";};
	protected:
	    
};


class Crop : public Filters
{
  public:
    Crop()  { Istart = Istop = Jstart = Jstop = -1; };
    const char *FilterName() { return "Crop"; };
    virtual void   Execute();
    void           SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
                      {
                        Istart = Istart_;
                        Istop  = Istop_;
                        Jstart = Jstart_;
                        Jstop  = Jstop_;
                      };

  private:
    int Istart, Istop, Jstart, Jstop;
};

class Transpose: public Filters
{ 
        public:
            void Execute();
            const char *FilterName(){return "Transpose";};
};
class Invert: public Filters
{ 
        public:
            void Execute();
            const char *FilterName(){return "Invert";};
};
class Checkerboard: public Filters
{ 
        public:
            void Execute();
            const char *FilterName(){return "Checkerboard";};
};
class Color: public Source
{
	protected:
	    int w_c;
	    int h_c;
	    unsigned char red;
	    unsigned char green;
	    unsigned char blue;

	public:
	    Color(int width, int height, unsigned char r, unsigned char g, unsigned char b)
		{
		//init color function to match the given main file
		w_c = width;
		h_c = height;
		red = r;
		green = g;
		blue = b;
		

		};
	    const char *SourceName(){return "ConstColor";};
	    const char *FilterName(){return "ConstColor";};
	    void Execute();

};
class CheckSum: public Sink
{
	public:
	    void OutputCheckSum(const char *f);
	    const char *SinkName(){return "CheckSum";};
};
#endif



