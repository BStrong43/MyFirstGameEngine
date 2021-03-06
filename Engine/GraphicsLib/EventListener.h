#pragma once

#include <Trackable.h>

class Event;
class EventSystem;

class EventListener :public Trackable
{
public:
	EventListener() {};
	EventListener(EventSystem* pEventSystem);
	virtual ~EventListener();

	virtual void handleEvent(const Event& theEvent) = 0;

private:
	EventSystem * mpEventSystem;//the event system this listener is listening to
protected:
	EventSystem * getEventSystem() const { return mpEventSystem; };
};