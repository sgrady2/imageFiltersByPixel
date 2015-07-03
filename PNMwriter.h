#include <Sink.h>
#include <stdio.h>
#include <iostream>
#ifndef PNMWRITER_H
#define PNMWRITER_H

class PNMwriter: public Sink
{
        public:
	    void Write(char *filename)
		{
		FILE *file = fopen(filename, "wb");
        	fprintf(file, "P6\n");
        	fprintf(file, "%d %d\n", input->getWidth(), input->getHeight());
      		fprintf(file, "%d\n", 255);
		fwrite(input->getBuffer(), sizeof(unsigned char), 3*input->getWidth()*input->getHeight(),file);
        	fclose(file);
		}
	    const char * SinkName(){return "PNMwriter";};

};

#endif



