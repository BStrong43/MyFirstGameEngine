#include "InputTranslator.h"
#include "EventListener.h"
#include "CreateEvent.h"
#include "DeleteEvent.h"
#include "MouseEvent.h"
#include "KeyEvent.h"

using namespace std;
//Constructors
InputTranslator::InputTranslator(EventSystem *eventSystem, System *system)
	:EventListener(eventSystem),
	mSystem(system)
{
	init(eventSystem);
}

InputTranslator::~InputTranslator()
 {
	cleanup();
 }

//Utility Functions
void InputTranslator::init(EventSystem* eventSystem) 
{
	eventSystem->getInstance()->addListener(KEYBOARD_EVENT, this);
	eventSystem->getInstance()->addListener(MOUSE_CLICK, this);
}

void InputTranslator::cleanup() {

}

void InputTranslator::handleEvent(const Event& theEvent) 
{

	if (theEvent.getType() == MOUSE_CLICK)
	{/*
		const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(theEvent);
		MouseEvent temp = mouseEvent;

		if (temp.getButton() == 1) 
		{
			EventSystem::getInstance()->fireEvent(CreateEvent(temp.getLocation()));
		}

		if (temp.getButton() == 2) 
		{
			EventSystem::getInstance()->fireEvent(DirecEvent(1));
		}*/
	}

	if (theEvent.getType() == KEYBOARD_EVENT)
	{
		const KeyEvent& keyboardEvent = static_cast<const KeyEvent&>(theEvent);
		KeyEvent temp = keyboardEvent;

		if (temp.getKey() == mSystem->getKey(ESC))
		{
			EventSystem::getInstance()->fireEvent(Event(QUIT_EVENT));
		}

		if (temp.getKey() == mSystem->getKey(ENTER))
		{
			EventSystem::getInstance()->fireEvent(Event(CREATE_EVENT));
		}

		if (temp.getKey() == mSystem->getKey(SPACE))
		{
			EventSystem::getInstance()->fireEvent(Event(PAUSE_EVENT));
		}

		if (temp.getKey() == mSystem->getKey(W))
		{
			EventSystem::getInstance()->fireEvent(DirecEvent(1));
		}

		if (temp.getKey() == mSystem->getKey(A))
		{
			EventSystem::getInstance()->fireEvent(DirecEvent(2));
		}

		if (temp.getKey() == mSystem->getKey(S))
		{
			EventSystem::getInstance()->fireEvent(DirecEvent(3));
		}

		if (temp.getKey() == mSystem->getKey(D))
		{
			EventSystem::getInstance()->fireEvent(DirecEvent(4));
		}
	}
}