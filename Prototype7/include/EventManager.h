//==========================//
// EventManager.h           //
// Author: Matthew Stephens //
//==========================//
#ifndef _EVENT_MANAGER_H
#define _EVENT_MANAGER_H

#include "Event.h"
#include "EventHandler.h"
#include <vector>

typedef std::vector<EventHandler*> EventHandlers;

//===================================================================================
// Class EventManager
// The EventManager is responsible for dispatching events to EventHandlers which
// have registered themselves with the EventManager.  An EventHandler is registered
// to respond to an event type with the addHandler() method. Events are dispatched
// with the triggerEvent() method, which calls each EventHandler for the event type,
// passing the Event::Data struct to the handler. The handlers are organized as an
// array of vectors of pointers to EventHandlers, where the event type is used as an
// index to the array.  The data members and methods of this class are static.
//===================================================================================
class EventManager
{
public:
	// Methods
	static void addHandler(int eventType, EventHandler *handler);
	static void triggerEvent(Event::Data e);
	
	static void clearHandlers();
	
private:
	static EventHandlers handlers[Event::NUM_TYPES];
};

#endif