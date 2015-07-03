#include <image.h>
#ifndef SOURCE_H
#define SOURCE_H


class Source{
        public:
            Image * GetOutput();
	    Source();
	    virtual void Update();
	    virtual const char * SourceName()=0;
	    void setSource();
	    virtual void Execute()=0;

	protected:
	    Image output;	    

};


#endif
