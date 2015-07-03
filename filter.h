#include <sink.h>
#include <source.h>

#ifndef FILTER_H
#define FILTER_H

class Filter: public Sink, public Source
{
	public:
	    virtual void Update();
	    virtual const char * FilterName()=0;
	    virtual const char *SourceName(){return FilterName();};
	    virtual const char *SinkName(){return FilterName();};

};
#endif





