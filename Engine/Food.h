#pragma once
#include "Unit.h"
#include <time.h>

class Food : public Unit {
public:
	//Constructors
	Food(GraphicsBuffer *buffer);
	~Food() { delete mBuffer; }

	//Accessors
	Vector2D getLocation() { return mLocation; }

	//Utility Functions
	Vector2D newLocation();

private:
	Vector2D mLocation;
	GraphicsBuffer *mBuffer;

};
