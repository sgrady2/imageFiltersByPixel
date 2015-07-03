#include <filter.h>
#include <logging.h>
void Filter::Update()
{
	//update img 1
	if (input != NULL){    
	    char msg[128];
	    sprintf(msg, "%s:about to update input1",SourceName());
	    Logger::LogEvent(msg);
	    input->Update();
	    sprintf(msg, "%s: done updating input1", SourceName());
	    Logger::LogEvent(msg);
			 
	   }	
	//update img 2
	if (input2 != NULL){
	    char msg[128];
	    sprintf(msg, "%s: about to update input2", SourceName());
	    Logger::LogEvent(msg);
	    input2->Update();
	    sprintf(msg, "%s: done updating input2", SourceName());
	    Logger::LogEvent(msg);
			}
	//execute
	Execute();
		
}
