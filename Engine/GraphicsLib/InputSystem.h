#pragma once
#include "GraphicsSystem.h"

class InputSystem : public Trackable {

public:
	//Constructors
	InputSystem() {};
	~InputSystem();

	void init();
	void cleanup();
	void update();

private:
	ALLEGRO_EVENT_QUEUE *mpEventQueue;
	ALLEGRO_EVENT *mpEvent;
};