#pragma once

#include "System.h"
#include "EventSystem.h"
#include "EventListener.h"
#include "Event.h"

class InputTranslator : public EventListener
{
public:
	//Constructors
	InputTranslator(EventSystem *eventSystem, System *system);
	~InputTranslator();

	//Utility Functions
	void init(EventSystem *eventSystem);
	void cleanup();
	virtual void handleEvent(const Event& evnt);

private:
	System *mSystem;
};
