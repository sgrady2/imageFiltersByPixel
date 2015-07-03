#include <filters.h>
#include <image.h>
#include <iostream>
#include <logging.h>
#include <filter.h>

using namespace std;

void Shrinker::Execute()
{
	output.ResetSize(input->getWidth()/2, input->getHeight()/2);
	int w = output.getWidth();
	int h = output.getHeight();
	for (int i =0;i<w;i++)
	{
		for (int j=0; j<h;j++)
		{
			unsigned char *pix = input->readPixel(2*i,2*j);
			output.writePixel(i, j, pix);
		}


	}
}
void LRConcat::Execute()
{
	if (input == NULL || input2 == NULL)
	{	
	    char msg[1024];
	    sprintf(msg, "%s: Not a valid first or second input!", SinkName());
            DataFlowException e(SinkName(), msg);
            throw e;
	}
	if (input->getHeight() != input2->getHeight())
	{
	    char msg[1024];
	    sprintf(msg, "%s: heights must match: %d %d",SinkName(), input->getHeight(), input2->getHeight() );
	    DataFlowException e(SinkName(), msg);
	    throw e;
	}	
	//initialize boundaries
	int l_w = input->getWidth();
        int l_h = input->getHeight();
        int r_w = input2->getWidth();
        int r_h = input2->getHeight();	

	//reset the size of the output to the combined witdths of the first and seco
	output.ResetSize(l_w+r_w, std::max(l_h, r_h));
	for (int i = 0;i < input->getWidth(); i++)
        {
                for (int j=0; j< input->getHeight();j++)
                {
                        unsigned char *l_pix = input->readPixel(i,j);
                        output.writePixel(i, j, l_pix);
                }
        }
	//now the right sideof output

	for (int i = 0;i < input2->getWidth(); i++)
        {
                for (int j=0; j< input2->getHeight();j++)
                {
                        unsigned char *r_pix = 	input2->readPixel(i,j);
                        //need to push this one to the right, so add the left width
                        output.writePixel((i+input->getWidth()), j, r_pix);
                }

	}
	
}
void TBConcat::Execute()
{	
	if (input->getWidth() != input2->getWidth())
        { 
            char msg[1024];
            sprintf(msg, "%s: widths must match: %d %d",SinkName(), input->getWidth(), input2->getWidth() );
            DataFlowException e(SinkName(), msg);
            throw e;
        }
	//doing the same as leftright but now with top and bottom
        int t_w = input->getWidth();
        int t_h = input->getHeight();
        int b_w = input2->getWidth();
        int b_h = input2->getHeight();
	
	//reset the size of the output to the combined heights of the first and seco
        if (t_w > b_w){
                output.ResetSize(t_w,t_h+b_h);}
        else{output.ResetSize(b_w,t_h+b_h);}
	
	//top first
	for (int i = 0;i < t_w; i++)
        {
                for (int j=0; j< t_h;j++)
                {
                        unsigned char *pix_t = input->readPixel(i, j);
                        output.writePixel(i, j, pix_t);
                }
        }
	//now bottom
	for (int i = 0;i < b_w; i++)
        {
                for (int j=0; j< b_h;j++)
                {
                        //need to push this one to the bottom, so add the top height
                        unsigned char *pix_b = input2->readPixel(i,j);
                        output.writePixel(i, j+t_h, pix_b);
                }

        }

}
void Crop::Execute()
{    
    // OneInputCheck();
    if (input==NULL){
        char msg[1024];
        sprintf(msg, "%s: input image is empty \n ", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;

        }
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istart >= input->getWidth() || Istop >= input->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Jstart >= input->getHeight() || Jstop >= input->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = input->getWidth();
    output.ResetSize(width, height);
    unsigned char *buffer = output.getBuffer();
    const unsigned char *buffer1 = input->getBuffer();
    for (int i = Istart ; i <= Istop ; i++)
    {
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
            buffer[3*idx]   = buffer1[3*idx1];
            buffer[3*idx+1] = buffer1[3*idx1+1];
            buffer[3*idx+2] = buffer1[3*idx1+2];
        }
    }
}



//Transpose an NXM image makes it an MXN image

void Transpose::Execute()
{
	if (input == NULL){
	char msg[1024];
	sprintf(msg, "%s: input image is empty \n ", FilterName());
	DataFlowException e(FilterName(), msg);
	throw e;

	}
	//reset the output image to be hXw instead of wXh
	output.ResetSize(input->getHeight(),input->getWidth());

	for (int i = 0;i<input->getHeight();i++)
	{
		for (int j = 0; j<input->getWidth();j++)
		{
		//setting the width to the height which transposes image matrix so reverse i and j
		unsigned char red = (input->readPixel(j,i)[0]);
		unsigned char green = (input->readPixel(j,i)[1]);
		unsigned char blue = (input->readPixel(j,i)[2]);
		unsigned char pix[] = {red, green, blue};
		output.writePixel(i, j, pix);		
		}
	}
	
}
void Invert::Execute()
{	
	if (input == NULL){
	char msg[1024];
        sprintf(msg, "%s: input image is empty \n ", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
	}

	//this time the output image will be the same NXM matrix, but inverted
	int h = input->getHeight();
	int w = input->getWidth();
	output.ResetSize(w, h);
	unsigned char val = 255;
	for (int i = 0;i<w;i++)
	{
        	for (int j = 0; j<h;j++)
                {
			//again creating a 3 color channels for each pixel
			//in my picture and then setting those 3 to their 
			//own unsigned char array
			unsigned char red = (val - (input->readPixel(i, j)[0]));
			unsigned char green = (val - (input->readPixel(i,j)[1]));
			unsigned char blue = (val - (input->readPixel(i,j)[2]));
			unsigned char pix[] = {red, green, blue};
			output.writePixel(i,j,pix);
		}
	}	

}
void Checkerboard::Execute()
{
	if (input==NULL)
	{
		char msg[1024];
        	sprintf(msg, "%s: input image is empty \n ", FilterName());
        	DataFlowException e(SinkName(), msg);
        	throw e;
	}
	if (input2==NULL)
        {
                char msg[1024];
                sprintf(msg, "%s: input2 image is empty \n ", FilterName());
                DataFlowException e(SinkName(), msg);
                throw e;
        }
	int h = input->getHeight();
	int w = input->getWidth();
	output.ResetSize(w,h);
	
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j< h;j++)
		{
			if ( (i/10+j/10) %2 == 0 )
			{
				unsigned char *pixif = input->readPixel(i,j);
				output.writePixel(i, j, pixif);
			}else{
				unsigned char *pixelse = input2->readPixel(i,j);
				output.writePixel(i,j,pixelse);
			}
			
		}


	}

}
void Color::Execute()
{
	//reset the img with protected data members of color w and h
	output.ResetSize(w_c, h_c);
	for (int i = 0; i<w_c;i++)
	{
		for (int j=0;j<h_c;j++)
		{
			output.getBuffer()[3*(j*w_c+i)+0] = red;
			output.getBuffer()[3*(j*w_c+i)+1] = green;
			output.getBuffer()[3*(j*w_c+i)+2] = blue;
		}	
	}
	


}
void Blender::Execute()
{

	if (input==NULL)
        {
                char msg[1024];
                sprintf(msg, "%s: input image is empty \n ", FilterName());
                DataFlowException e(SinkName(), msg);
                throw e;
        }
        if (input2==NULL)
        {
                char msg[1024];
                sprintf(msg, "%s: input2 image is empty \n ", FilterName());
                DataFlowException e(SinkName(), msg);
                throw e;
        }
	if (input->getWidth() != input2->getWidth())
	{
		char msg[1024];
        	sprintf(msg, "%s: check width:%d, %d", FilterName(), input->getWidth(), input2->getWidth());
        	DataFlowException e(FilterName(),msg);
        	throw e;
	
	}	

	if (bf > 1 || bf < 0)
	{   
	    char msg[1024];
            sprintf(msg, "%s: check blend factor: %f",FilterName(), bf);
            DataFlowException e(SinkName(), msg);
            throw e;
	}
	else{
		int w = input->getWidth();
		int h = input->getHeight();
		output.ResetSize(w,h);
		for (int i=0;i<w;i++)
                {
                        for(int j=0;j<h;j++)
                        {
				//for each pixel in the picture I want to create a 
				//channel for rgb to write to, then pass that 
				//3 color channel to the pixel i,j that im at
				
				unsigned char red = input->readPixel(i,j)[0]*bf+input2->readPixel(i,j)[0]*(1-bf);
				unsigned char green = input->readPixel(i,j)[1]*bf+input2->readPixel(i,j)[1]*(1-bf);
				unsigned char blue = input->readPixel(i,j)[2]*bf+input2->readPixel(i,j)[2] *(1-bf);
				unsigned char pix[] = {red, green, blue};
				output.writePixel(i, j, pix);
				
                        }
		}

	}
}
void CheckSum::OutputCheckSum(const char *file)
{	//would normally have to do a mod 256 operation but not for unsigned char 	
	if (input == NULL){
        char msg[1024];
        sprintf(msg, "%s: empty input \n ", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
	}

	FILE* sumfile = fopen(file, "w");
	int h = input->getHeight();
	int w = input->getWidth();

	unsigned char rsum = 0;
	unsigned char gsum = 0;
	unsigned char bsum = 0;

	for (int i = 0; i< w;i++)
	{
		for (int j=0;j<h;j++)
		{	//sum each color channel of the input image
			rsum += input->getBuffer()[3*(j*w+i)+0];
			gsum += input->getBuffer()[3*(j*w+i)+1];
			bsum += input->getBuffer()[3*(j*w+i)+2];
		}
	}
	fprintf(sumfile, "CHECKSUM: %d, %d, %d\n", rsum, gsum, bsum);
	fclose(sumfile);

}
