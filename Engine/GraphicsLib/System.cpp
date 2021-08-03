#include "System.h"

System::System(int width, int height) 
{
	mWidth = width;
	mHeight = height;
	init();
}

System::~System() 
{
	cleanUp();
}

void System::update() {
	mInputSystem->update();
}

void System::updateInput() {
	mInputSystem->update();
}

void System::init()
{
	if (isInit == false) {
		mGraphicsSystem = new GraphicsSystem(mWidth, mHeight);
		mGraphicsSystem->init();
		mInputSystem = new InputSystem();
		mInputSystem->init();
		mKeyState = new ALLEGRO_KEYBOARD_STATE;
		mMouseState = new ALLEGRO_MOUSE_STATE;
		isInit = true;
	}
}

void System::flip() 
{
	mGraphicsSystem->flip();
}

void System::cleanUp()
{
	mGraphicsSystem->cleanUp();
	delete mGraphicsSystem;
	mInputSystem->cleanup();
	delete mInputSystem;
}


//Makes sure that the keys are only pressed once. When the key is released the key can be pressed again 
bool System::getKeyState(int keycode, bool &keyState) 
{ 
	al_get_keyboard_state(mKeyState);

	
	if (!al_key_down(mKeyState, keycode))
		keyState = false;
	else if(!keyState) 
	{
		keyState = true;
		return true;
	}
		
	return false;
	
}

//Makes sure that the left mouse button can only be checked one per pressed button. If its pressed return the location of the mouse
//Else return -1,-1
Vector2D System::getMouseState(bool &mouseState) 
{
	al_get_mouse_state(mMouseState);
	if (!al_mouse_button_down(mMouseState, 1))
		mouseState = false;
	else if (!mouseState) 
	{
		mouseState = true;
		return Vector2D(mMouseState->x, mMouseState->y);
	}
	return Vector2D(-1,-1); 

}

//Makes sure that the right mouse button can only be checked one per pressed button. If its pressed return the location of the mouse
//Else return -1,-1
Vector2D System::getRightMouse(bool& mouseState)
{
	al_get_mouse_state(mMouseState);
	if (!al_mouse_button_down(mMouseState, 2))
		mouseState = false;
	else if (!mouseState)
	{
		mouseState = true;
		return Vector2D(mMouseState->x, mMouseState->y);
	}
	return Vector2D(-1, -1);
}

void System::render(Vector2D loc, Sprite* sprite, float scale)
{
	mGraphicsSystem->draw(loc, sprite, scale);
}
