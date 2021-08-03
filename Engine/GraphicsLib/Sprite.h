#pragma once
#include "Vector2D.h"
#include "GraphicsBuffer.h"
#include "Trackable.h"


class Sprite : public Trackable
{
	
public:
	friend class GraphicsSystem;
	Sprite();
	~Sprite();
	Sprite(GraphicsBuffer* buffer, Vector2D loc);
	Sprite(GraphicsBuffer* buffer, Vector2D loc, Vector2D dimensions );

	int getHeight() { return mHeight; }
	int getWidth() { return mWidth; }
	Vector2D getLocation() { return mLoc; }
	GraphicsBuffer* getBitmap() { return mBuffer;}
	void setLocX(float x) { mLoc.setX(x); }
	void setLocY(float y) { mLoc.setY(y); }

private:
	GraphicsBuffer* mBuffer;
	Vector2D mLoc;
	int mHeight;
	int mWidth;
};