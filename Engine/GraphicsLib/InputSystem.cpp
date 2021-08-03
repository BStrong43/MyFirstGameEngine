#include "InputSystem.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "EventSystem.h"
#include "Event.h"

InputSystem::~InputSystem() {
	
}

void InputSystem::init()
{
	//Init Allegro Input
	if (!al_install_keyboard())
	{
		system("pause");
	}
	if (!al_install_mouse())
	{
		system("pause");
	}
	//Init Data
	mpEventQueue = al_create_event_queue();
	mpEvent = new ALLEGRO_EVENT;
	
	//Register Data with Allegro
	al_register_event_source(mpEventQueue, al_get_keyboard_event_source());
	al_register_event_source(mpEventQueue, al_get_mouse_event_source());
}

void InputSystem::cleanup()
{
	delete mpEvent;
	al_flush_event_queue(mpEventQueue);
	al_destroy_event_queue(mpEventQueue);
}

void InputSystem::update() {
	
	while (!al_event_queue_is_empty(mpEventQueue)) {
		//Grab next event in queue
		al_get_next_event(mpEventQueue, mpEvent);
		
		//check if type of event is mouse
		if (mpEvent->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			//get relevant info from mouse
			float x = mpEvent->mouse.x,
				  y = mpEvent->mouse.y;

			Vector2D loc = Vector2D(x, y);

			int click = mpEvent->mouse.button;
			//Fire mouse event
			EventSystem::getInstance()->fireEvent(MouseEvent(loc, click));
		}

		//check if type of event is key
		if (mpEvent->type == ALLEGRO_EVENT_KEY_DOWN) {
			//Get relevant info about downed key
			int key = mpEvent->keyboard.keycode;

			//Fire key event
			EventSystem::getInstance()->fireEvent(KeyEvent(key));
		}
	}
}