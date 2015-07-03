#include <Source.h>
#include <String.h>
#ifndef PNMREADER_H
#define PNMREADER_H

class PNMreader: public Source
{
        public:
            virtual void Execute();
            PNMreader(const char *p);
    	    virtual ~PNMreader();
	    const char *SourceName();
        protected:
            char* filestring;
};
#endif
