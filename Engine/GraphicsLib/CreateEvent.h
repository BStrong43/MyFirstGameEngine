#pragma once

#include "Event.h"
#include "Vector2D.h"

class CreateEvent : public Event
{

public:
	//Constructors
	CreateEvent(Vector2D loc) :Event(CREATE_EVENT), mLoc(loc) {};
	~CreateEvent() {};

	//Accessor
	Vector2D getLocation() { return mLoc; };

private:
	Vector2D mLoc;
};

