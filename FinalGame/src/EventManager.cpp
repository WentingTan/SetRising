//==========================//
// EventManager.cpp         //
// Author: Matthew Stephens //
//==========================//
#include "EventManager.h"

EventHandlers EventManager::handlers[Event::NUM_TYPES];

//=============================================================================
// EventManager::addHandler(int,EventHandler*)
// This method registers an EventHandler to respond to an event type by adding
// a pointer to it to the vector of pointers in the handlers array.
//=============================================================================
void EventManager::addHandler(int eventType, EventHandler *handler)
{
	if (eventType < Event::NUM_TYPES)
		handlers[eventType].push_back(handler);
}

// ============================================================================
// EventManager::triggerEvent(Event::Data)
// Dispatches an event to the EventHandlers that have registered to respond to
// it. The event type acts an index in to the handlers array to retrieve the
// vector of EventHandler pointers. The event is handled by the handleEvent()
// method of classes derived from EventHandler.
// ============================================================================
void EventManager::triggerEvent(Event::Data e)
{
	for (int i = 0; i < handlers[e.type].size(); i++)
		handlers[e.type][i]->handleEvent(e);
}

void EventManager::clearHandlers()
{
	for (int i = 0; i < Event::NUM_TYPES; i++)
		handlers[i].clear();
}