#include <sink.h>
#include <image.h>

void Sink::SetInput(const Image *input_)
{
	this->input = input_;
}
void Sink::SetInput2(const Image *input2_)
{
	this->input2 = input2_;
}
Sink::~Sink()
{

}
