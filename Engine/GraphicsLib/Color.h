#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "Trackable.h"

class Color: public Trackable
{
public:
	friend class GraphicsSystem;
	friend class Unit;
private:
	//friend class GraphicsSystem;

	static ALLEGRO_COLOR getWhite();
	static ALLEGRO_COLOR getRed();
	static ALLEGRO_COLOR getBlack();
	static ALLEGRO_COLOR clear();
};
