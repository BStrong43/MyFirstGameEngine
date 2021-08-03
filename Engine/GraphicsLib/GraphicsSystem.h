#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "Font.h"
#include "Color.h"
#include <string>
#include "Trackable.h"

class GraphicsSystem : public Trackable
{
public:
	
	GraphicsSystem(int width, int height);
	~GraphicsSystem();

	void init();
	void cleanUp();
	void flip();
	int getHeight() { return mHeight; }
	int getWidth() { return mWidth; }
	GraphicsBuffer* getBackBuffer() { return mBackBuffer; }

	void draw(Vector2D loc, Sprite* sprite, float scale = 1.0);
	void draw(GraphicsBuffer* buffer, Vector2D loc, Sprite* sprite, float scale = 1.0);
	void drawColor(GraphicsBuffer* buffer, Color* color);
	void writeText(Vector2D loc, Font* font, Color* color, std::string text);
	void writeText(GraphicsBuffer* buffer, Vector2D loc, Font* font, Color* color, std::string text);

	void saveBuffer(std::string filename, GraphicsBuffer* buffer);

private:
	int mHeight;
	int mWidth;
	bool isInit = false;
	ALLEGRO_DISPLAY* mDisplay;
	GraphicsBuffer* mBackBuffer;
};