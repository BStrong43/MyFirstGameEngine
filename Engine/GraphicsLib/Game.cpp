#include "Game.h"
#include "Timer.h"

Game::Game(int width, int height)
{
	mWidth = width;
	mHeight = height;
}
Game::~Game() 
{

}

void Game::init() 
{
	mSystem = new System(mWidth, mHeight);
	mSystem->init();
}
void Game::cleanUp() 
{

	
	mSystem->cleanUp();
	delete mSystem;
	for (int i = 0; i < buffers.size(); i++) {
		delete buffers[i];
	}
	buffers.clear();

	for (int i = 0; i < units.size(); i++) {
		delete units[i];
	}
	units.clear();
}

void Game::doLoop() 
{
	Timer time;
	isRunning = true;
	time.start();
	double lastTime = time.getElapsedTime();

	while (isRunning) {
		float current = time.getElapsedTime();
		float elapsed = current - lastTime;
		processInput();
		update(elapsed);
		draw();
		lastTime = current;
		al_rest(16.7 - current - time.getElapsedTime());
	}

	time.stop();
}

void Game::update(float timePass)
{
	for (int i = 0; i < units.size(); i++)
		units[i]->update(timePass);
}

void Game::draw()
{
	for (int i = 0; i < units.size(); i++)
		units[i]->draw(mSystem);

	mSystem->flip();
}

void Game::processInput()
{
	//ESACPE key
	if (mSystem->getKeyState(59, escPressed)) 
		isRunning = false;
	

	//F key
	if (mSystem->getKeyState(6, fPressed)) 
		units[1]->getAnimation()->changeSpeed(-5.0);
	

	//S Key 
	if (mSystem->getKeyState(19, sPressed)) 
		units[1]->getAnimation()->changeSpeed(5.0);
	

	//ENTER key 
	if (mSystem->getKeyState(67, enterPressed)) 
		units[1]->changeAnimation();

		
}

void Game::addSprite(int width, int height, Vector2D loc) {
	Sprite* sprite = new Sprite(new GraphicsBuffer(width, height), loc);
	Animation* anim = new Animation(sprite);
	Unit* temp = new Unit(loc, anim);
	units.push_back(temp);
}
void Game::addSprite(std::string path, Vector2D loc) {
	Unit* temp = new Unit(loc, new Animation(new Sprite(new GraphicsBuffer(path), loc)));
	units.push_back(temp);
}

void Game::addSpriteSheet(std::string path, Vector2D loc, Vector2D dimensions) {
	Sprite sprite(new GraphicsBuffer(path), loc);
	Animation* anim = new Animation(16.7);
	for (int i = 0; i < sprite.getHeight() / dimensions.getY(); i++) {
		for (int j = 0; j < sprite.getWidth() / dimensions.getX(); j++) {
			anim->addSpriteToAnimation(new Sprite(sprite.getBitmap(), Vector2D(j*dimensions.getX(), i*dimensions.getY()), dimensions));
		}
	}
	anim->setCurrentSprite(0);
	Unit* temp = new Unit(loc, anim);
	units.push_back(temp);
}

void Game::addAnimation(int unitIndex, std::string path, Vector2D dimensions) {
	Sprite sprite(new GraphicsBuffer(path), units[unitIndex]->getLocation());
	Animation* anim = new Animation(units[unitIndex]->getAnimation()->getSpeed());
	for (int i = 0; i < sprite.getHeight() / dimensions.getY(); i++) {
		for (int j = 0; j < sprite.getWidth() / dimensions.getX(); j++) {
			anim->addSpriteToAnimation(new Sprite(sprite.getBitmap(), Vector2D(j*dimensions.getX(), i*dimensions.getY()), dimensions));
		}
	}
	anim->setCurrentSprite(0);
	units[unitIndex]->addAnimation(anim);
}
