#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Trackable.h"

#include <string>
class GraphicsBuffer : public Trackable
{
public:
	friend class GraphicsSystem;
	friend class Sprite;
	friend class Unit;

	GraphicsBuffer(std::string fileName);
	GraphicsBuffer(GraphicsBuffer *buffer);
	~GraphicsBuffer();
	GraphicsBuffer(int width, int height);

	int getHeight() { return mHeight; }
	int getWidth() { return mWidth; }
	ALLEGRO_BITMAP* mBitmap;

private:
	int mHeight;
	int mWidth;

};