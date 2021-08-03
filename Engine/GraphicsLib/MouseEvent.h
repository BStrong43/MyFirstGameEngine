#pragma once

#include "Event.h"
#include "Vector2D.h"

class MouseEvent : public Event 
{

public:
	//Constructors
	MouseEvent(Vector2D loc, int click) :Event(MOUSE_CLICK), mClick(click)
	{ mLoc = loc; };
	
	~MouseEvent() {};

	//Accessors
	Vector2D getLocation() { return mLoc; }
	int getButton() { return mClick; }

private:
	Vector2D mLoc;
	int mClick;

};