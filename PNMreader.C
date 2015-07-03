#include <PNMreader.h>
#include <stdio.h>
void PNMreader::Execute()
{	
	FILE *file = fopen(filestring, "rb");
	char magicNum[64];
	if (file == NULL){
	printf("nofile");
	}
	int width, height, maxVal;
	fscanf(file, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxVal);
	output.ResetSize(width, height);
	unsigned char *data = output.getBuffer();
	fread(data, sizeof(unsigned char), width*height*3, file);
	fclose(file);
}
PNMreader::~PNMreader()
{
	if (filestring != NULL){
	    delete [] filestring;
	}
}
PNMreader::PNMreader(const char *p)
{
       //add the \n char with +1
       filestring = new char[strlen(p)+1];
       strcpy(filestring, p);
}
const char * PNMreader::SourceName(){return "PNMreader";}
