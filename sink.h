#include <image.h>
#ifndef SINK_H
#define SINK_H
class Sink{
	public:
	    virtual const char * SinkName()=0;
	    void SetInput(const Image *input1_);
	    void SetInput2(const Image *input2_);
		//default
	    Sink(){
		input=NULL;
		input2=NULL;
			};
	    virtual ~Sink();
	protected:
	    const Image *input;
	    const Image *input2;    
};
#endif
