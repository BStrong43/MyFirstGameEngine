#include "Color.h"

//Returns white
ALLEGRO_COLOR Color:: getWhite()
{
	return al_map_rgb(255, 255, 255);
}

//returns red
ALLEGRO_COLOR Color::getRed() 
{
	return al_map_rgb(255, 0, 0);
}

//Returns black 
ALLEGRO_COLOR Color::getBlack()
{
	return al_map_rgb(0, 0, 0);
}

ALLEGRO_COLOR Color::clear()
{
	return al_map_rgba(1.0, 1.0, 0, 0);
}