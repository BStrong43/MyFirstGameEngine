#include "Food.h"

Food::Food(GraphicsBuffer *buffer) 
{
	mBuffer = buffer;
	addAnimation(new Animation(new Sprite(mBuffer, Vector2D(0,0))));
	newLocation();
	srand(time(NULL));
}

Vector2D Food::newLocation() 
{
	int x, y;

	//Random grid coords
	x = rand() % 20;
	y = rand() % 14;

	//convert to screen coords
	x *= 40;
	y *= 40;

	mLocation.setX(x);
	mLocation.setY(y);
	setLocation(mLocation);
	return mLocation;
}