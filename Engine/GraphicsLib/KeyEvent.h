#pragma once
#include "Event.h"

class KeyEvent : public Event {

public:
	//Constructors
	KeyEvent(int key) :Event(KEYBOARD_EVENT), mKey(key) {};
	~KeyEvent() {};

	int getKey() { return mKey; }

private:
	int mKey;
};
