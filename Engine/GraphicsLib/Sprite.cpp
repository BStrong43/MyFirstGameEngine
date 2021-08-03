#include "Sprite.h"

//Creates a sprite to a specific buffer with a location and dimensions 
Sprite::Sprite(GraphicsBuffer* buffer, Vector2D loc, Vector2D dimensions)
{
	mLoc = loc;
	mBuffer = buffer;
	mWidth = dimensions.getX();
	mHeight = dimensions.getY();
	assert(mBuffer);
}
//Creates a sprite to a specific buffer with a location and dimensions 
Sprite::Sprite(GraphicsBuffer* buffer, Vector2D loc)
{
	mLoc = loc;
	mBuffer = buffer;
	mWidth = mBuffer->getWidth();
	mHeight = mBuffer->getHeight();
	assert(mBuffer);
}

Sprite::~Sprite() 
{
}
Sprite::Sprite() 
{}