#include "GraphicsSystem.h"
#include <string>

//Creates a screen with the height and width
GraphicsSystem:: GraphicsSystem(int width, int height) 
{
	mWidth = width;
	mHeight = height;
	
}

//Deletes the back Buffer
GraphicsSystem::~GraphicsSystem() 
{
	cleanUp();
}

//Initializes the addons used in the program
void GraphicsSystem::init()
{
	if (!al_init())
	{
		std::cout << "error initting Allegro\n";
		system("pause");
	}
	if (!al_init_image_addon())
	{
		std::cout << "error initting image add-on\n";
		system("pause");
	}

	if (!al_init_font_addon()) 
	{
		std::cout << "error initting font add-on\n";
		system("pause");
	}

	if (!al_init_ttf_addon()) 
	{
		std::cout << "error initting ttf add-on\n";
		system("pause");
	}

	if (!al_init_primitives_addon()) 
	{
		std::cout << "error initting primitives add-on\n";
		system("pause");
	}

	if (!al_init_acodec_addon()) 
	{
		std::cout << "error initting acodec add-on\n";
		system("pause");
	}

	if (!al_install_audio()) 
	{
		std::cout << "error initting audio add-on\n";
		system("pause");
	}

	if (!al_reserve_samples(1))
	{
		std::cout << "error reserving samples\n";
		system("pause");
	}

	//create the display
	mDisplay = al_create_display(mWidth, mHeight);
	assert(mDisplay);
	mBackBuffer = new GraphicsBuffer(mWidth, mHeight);
	assert(mBackBuffer);


	mBackBuffer->mBitmap = al_get_backbuffer(mDisplay);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	isInit = true;
}

//destorys the display 
void GraphicsSystem::cleanUp() 
{
	if (isInit &&  mDisplay != nullptr) {
		al_destroy_display(mDisplay);
		delete mBackBuffer;

		al_shutdown_font_addon();
		al_shutdown_image_addon();
		al_shutdown_primitives_addon();
		al_shutdown_ttf_addon();

		isInit = false;
	}
}

//Displays the back buffer
void GraphicsSystem::flip()
{
	al_flip_display();
}

//Draws to the back buffer
void GraphicsSystem::draw(Vector2D loc, Sprite* sprite, float scale) 
{
	draw(getBackBuffer(), loc, sprite, scale);
}

//Draws to a specific buffer
void GraphicsSystem::draw(GraphicsBuffer* buffer, Vector2D loc, Sprite* sprite, float scale) 
{
	al_set_target_bitmap(buffer->mBitmap);
	al_draw_tinted_scaled_rotated_bitmap_region(sprite->getBitmap()->mBitmap, sprite->getLocation().getX(), sprite->getLocation().getY(), sprite->getWidth(), sprite->getHeight(), Color::getWhite(), 0,0,loc.getX(), loc.getY(), scale, scale, 0,0);


	
}

//Draws red to a specific buffer
void GraphicsSystem::drawColor(GraphicsBuffer* buffer, Color* color) 
{
	al_set_target_bitmap(buffer->mBitmap);
	al_clear_to_color(color->getRed());
}

//writes text to the back buffer
void GraphicsSystem::writeText(Vector2D loc, Font* font, Color* color, std::string text)
{
	writeText(getBackBuffer(), loc, font, color, text);
}


//Writes text to a specific buffer
void GraphicsSystem::writeText(GraphicsBuffer* buffer, Vector2D loc, Font* font, Color* color, std::string text)
{
	
	al_set_target_bitmap(buffer->mBitmap);
	al_draw_text(font->mFont, color->getBlack(), loc.getX(), loc.getY(), ALLEGRO_ALIGN_CENTER, text.c_str());
}

//Saves a specific buffer to a file
void GraphicsSystem::saveBuffer(std::string filename, GraphicsBuffer* buffer)
{
	al_save_bitmap(filename.c_str(), buffer->mBitmap);
}