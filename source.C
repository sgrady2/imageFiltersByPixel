#include <image.h>
#include <stdlib.h>
#include <source.h>
#include <logging.h>
//creates an instance of a source giving the output image the correct src

Source::Source(){
	output.setSource(this);
}
Image * Source::GetOutput()
{
	return &output;

}

void Source::Update()
{
	char msg[1024];
	sprintf(msg, "%s:about to execute", SourceName());
	Logger::LogEvent(msg);
	Execute();
	sprintf(msg, "%s:done executing", SourceName());
	Logger::LogEvent(msg);
}
