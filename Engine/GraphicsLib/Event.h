#pragma once

#include <string>
#include "Trackable.h"

using namespace std;

enum EventType{
	INVALID_EVENT = -1,
	KEYBOARD_EVENT,
	MOUSE_CLICK,
	CREATE_EVENT,
	PAUSE_EVENT,
	DIREC_EVENT,
	CHANGE_ANIM,
	QUIT_EVENT,
	NUM_EVENT_TYPES
};

const string EVENT_NAMES[8] = { 
	"Key Event",
	"Mouse Event",
	"Create Event",
	"Pause",
	"Delete Event",
	"Change Animation",
	"Quit Game"
};

class Event :public Trackable
{
public:
	Event(EventType type);
	virtual ~Event();

	EventType getType() const { return mType; };
	const string& getEventName() const;

private:
	EventType mType;

};