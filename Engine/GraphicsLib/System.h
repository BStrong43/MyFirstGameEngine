#pragma once
#include "GraphicsSystem.h"
#include "InputSystem.h"

enum Keys {
	NULL_KEY = -1,
	W,
	S,
	A,
	D,
	ESC,
	ENTER,
	SPACE,
	NUM_of_KEYS
};

class System : public Trackable
{
public:
	friend class Unit;
	System(int width, int height);
	System();
	~System();

	void init();
	void cleanUp();
	void update();
	void render(Vector2D loc, Sprite *sprite, float scale = 1.0f);
	void flip();
	void updateInput();

	bool getKeyState(int keycode, bool &keyState);
	Vector2D getMouseState(bool &mouseState);
	Vector2D getRightMouse(bool &mouseState);
	int getKey(Keys key) { return inputKeys[key]; }
	GraphicsSystem* getGraphicsSystem() { return mGraphicsSystem; }

private:
	GraphicsSystem* mGraphicsSystem;
	InputSystem *mInputSystem;
	ALLEGRO_KEYBOARD_STATE* mKeyState;
	ALLEGRO_MOUSE_STATE* mMouseState;
	int mWidth, mHeight;
	bool isInit = false;
	
	int inputKeys[NUM_of_KEYS] = { ALLEGRO_KEY_W,
		ALLEGRO_KEY_S,
		ALLEGRO_KEY_A,
		ALLEGRO_KEY_D,
		ALLEGRO_KEY_ESCAPE,
		ALLEGRO_KEY_ENTER,
		ALLEGRO_KEY_SPACE };
};