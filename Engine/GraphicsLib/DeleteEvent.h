#pragma once

#include "Event.h"
#include "Vector2D.h"

class DirecEvent : public Event 
{

public:
	//Constructors
	DirecEvent(int direc) :Event(DIREC_EVENT), direction(direc) {};
	~DirecEvent() {};

	//Accessor
	int getDirec() { return direction; };

private:
	int direction;
};
