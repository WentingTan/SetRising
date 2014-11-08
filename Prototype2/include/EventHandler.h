//==========================//
// EventHandler.h           //
// Author: Matthew Stephens //
//==========================//
#ifndef _EVENT_HANDLER_H
#define _EVENT_HANDLER_H

#include "Event.h"

class EventHandler
{
public:
	// Constructor
	//EventHandler();
	// Destructor
	//~EventHandler();
	
	// Methods
	virtual void handleEvent(Event::Data e) = 0;
};

#endif