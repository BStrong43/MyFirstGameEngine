#include "Font.h"
#include <iostream>

//Creates a font 
Font::Font(float size, std::string path)
{
	mFont = al_load_ttf_font(path.c_str(), size, 0);
	mFontSize = size;
}

//Destroys the font
Font::~Font() 
{
	//al_destroy_font(mFont);
}