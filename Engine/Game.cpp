#include "Game.h"
#include "Timer.h"
#include "PerformanceTracker.h"
#include "DeleteEvent.h"
#include <sstream>

Game* Game::mpInstance = NULL;

Game* Game::getInstance()
{
	assert(mpInstance != NULL);
	return mpInstance;
}

Game::Game(EventSystem *eventSystem, int width, int height)
	:EventListener(eventSystem)
{

	mWidth = width;
	mHeight = height;
}

Game::~Game() 
{

}

void Game::init(EventSystem *eventSystem, std::string groundPath) 
{
	if (mpInstance == NULL)
	{
		mpInstance = new Game(eventSystem);
		mpInstance->mEventSystem = eventSystem;
		eventSystem->addListener(QUIT_EVENT, mpInstance);
		eventSystem->addListener(CREATE_EVENT, mpInstance);
		eventSystem->addListener(DIREC_EVENT, mpInstance);
	}

	mpInstance->mSystem = new System(mpInstance->mWidth, mpInstance->mHeight);
	mpInstance->mSystem->init();

	mpInstance->mGBM = new GraphicsBufferManager;
	mpInstance->mUM = new UnitManager(mpInstance->mSystem);

	mpInstance->mTranslator = new InputTranslator(EventSystem::getInstance(), mpInstance->mSystem);
	mpInstance->mTranslator->init(EventSystem::getInstance());

	mpInstance->mLM = new LevelManager();
	mpInstance->mSpritePath = groundPath;
}

void Game::cleanUp() 
{
	//clean up
	mpInstance->mSystem->cleanUp();
	mpInstance->mGBM->clear();
	mpInstance->mUM->clear();
	mpInstance->mLM->cleanup();

	delete mpInstance->mSystem;
	delete mpInstance->mGBM;
	delete mpInstance->mUM;
	delete mpInstance;
	mpInstance = NULL;
}

void Game::doLoop() 
{
	PerformanceTracker* tracker = new PerformanceTracker;
	Timer time;
	mIsRunning = true;

	time.start();
	double lastTime = time.getElapsedTime();
	

	while (mIsRunning) 
	{
		tracker->startTracking("frame");
		time.pause(false);

		double current = time.getElapsedTime();
		double elapsed = current - lastTime;
		
		processInput();
		update(elapsed);
		draw();

		lastTime = current;

		time.sleepUntilElapsed(16.7);

		time.pause(true);
		
		//std::cout << tracker->getElapsedTime("frame") << std::endl;
		mHUD->checkFPS(tracker->getElapsedTime("frame"));
		tracker->removeTracker("frame");
	}

	time.stop();
	delete tracker;
}

//Updates each of the units in the game (in this build everything is a unit)
void Game::update(float timePass)
{
	mpInstance->mUM->update(timePass);
	checkFoodCol();
	checkSnakeWall();
	checkSnakeLive();
	checkSnakeSize();
}

//Draw each of the units in the game (in this build everything is a unit)
void Game::draw()
{
	mpInstance->mUM->draw();
	mSystem->flip();
}

//Gets the input 
void Game::processInput()
{
	mSystem->updateInput();
}

//creats a buffer to create a sprite to create an animation to create a unit. Both the buffer and unit are added to their managers
void Game::addSprite(int width, int height, Vector2D loc, std::string buffname, float scale) 
{
	Unit* temp = new Unit(loc, new Animation(new Sprite(new GraphicsBuffer(width, height), loc)), scale);
	mpInstance->mGBM->addBuffer(buffname, temp->getAnimation()->getCurrentSprite()->getBitmap());
	mpInstance->mUM->addUnit(temp);
}

//creats a buffer to create a sprite to create an animation to create a unit. Both the buffer and unit are added to their Managers
void Game::addSprite(std::string path, Vector2D loc, std::string buffname, float scale) 
{
	Unit* temp = new Unit(loc, new Animation(new Sprite(new GraphicsBuffer(path), loc)), scale);
	mpInstance->mGBM->addBuffer(buffname, temp->getAnimation()->getCurrentSprite()->getBitmap());
	mpInstance->mUM->addUnit(temp);
}

//Splits a spritesheet up into sprites and adds it to a animation 
void Game::addSpriteSheet(std::string path, Vector2D loc, Vector2D dimensions, std::string buffname, float scale) 
{
	GraphicsBuffer *buffer = new GraphicsBuffer(path);
	Unit* temp = new Unit(loc, new Animation(50.1f), scale);
	
	for (int i = 0; i < buffer->getHeight() / dimensions.getY(); i++)
		for (int j = 0; j < buffer->getWidth() / dimensions.getX(); j++) 
			temp->getAnimation()->addSpriteToAnimation(new Sprite(buffer, Vector2D(j*dimensions.getX(), i*dimensions.getY()), dimensions));
		
	temp->getAnimation()->setCurrentSprite(0);

	mpInstance->mGBM->addBuffer(buffname, buffer);
	mpInstance->mUM->addUnit(temp);
}

//Splits a spritesheets up into sprites and added to an existing unit's animation 
void Game::addAnimation(int unitIndex, std::string path, Vector2D dimensions, std::string buffname)
{
	GraphicsBuffer *buffer = new GraphicsBuffer(path);
	Animation* anim = new Animation(mpInstance->mUM->getUnit(unitIndex)->getAnimation()->getSpeed());

	for (int i = 0; i < buffer->getHeight() / dimensions.getY(); i++) 
		for (int j = 0; j < buffer->getWidth() / dimensions.getX(); j++) 
			anim->addSpriteToAnimation(new Sprite(buffer, Vector2D(j*dimensions.getX(), i*dimensions.getY()), dimensions));
		
	anim->setCurrentSprite(0);
	mpInstance->mGBM->addBuffer(buffname, buffer);
	mpInstance->mUM->getUnit(unitIndex)->addAnimation(anim);
}

//Creates a new Unit for the list
void Game::newUnit(GraphicsBuffer* buffOne, GraphicsBuffer* buffTwo, Vector2D loc, Vector2D dimensions, float scale)
{
	//Create unit and first animation
	Unit* temp = new Unit(loc, new Animation(50.1f), scale);

	for (int i = 0; i < buffOne->getHeight() / dimensions.getY(); i++)
		for (int j = 0; j < buffOne->getWidth() / dimensions.getX(); j++)
			temp->getAnimation()->addSpriteToAnimation(new Sprite(buffOne, Vector2D(j*dimensions.getX(), i*dimensions.getY()), dimensions));

	temp->getAnimation()->setCurrentSprite(0);

	//Create second animation and add it to the new unit
	Animation* anim = new Animation(50.1f);

	for (int i = 0; i < buffTwo->getHeight() / dimensions.getY(); i++)
		for (int j = 0; j <buffTwo->getWidth() / dimensions.getX(); j++)
			anim->addSpriteToAnimation(new Sprite(buffTwo, Vector2D(j*dimensions.getX(), i*dimensions.getY()), dimensions));

	anim->setCurrentSprite(0);
	temp->addAnimation(anim);

	//Add the unit to Unit Manager
	mpInstance->mUM->addUnit(temp);
}

void Game::handleEvent(const Event& theEvent) 
{
	if (theEvent.getType() == QUIT_EVENT)
		mIsRunning = false;

	if (theEvent.getType() == CREATE_EVENT) {
		if (mSnake->snakeLive()) {
			mSnake->resetSnake();
			mHUD->resetScore();
		}
	}
	
	if (theEvent.getType() == DIREC_EVENT) {
		const DirecEvent& direc = static_cast<const DirecEvent&>(theEvent);
		DirecEvent temp = direc;
		mSnake->changeDirection(temp.getDirec());
	}
}

void Game::newSnake(std::string filePath, Vector2D loc, float scale) 
{
	GraphicsBuffer *buffer = new GraphicsBuffer(filePath);
	Snake *snake = new Snake(loc, buffer);
	snake->addAnimation(new Animation(new Sprite(buffer,loc)));
	mpInstance->mGBM->addBuffer("snake", buffer);
	mpInstance->mUM->addUnit(snake);
	mSnake = snake;
}

void Game::newHUD(std::string filePath, std::string dataFile, Vector2D loc, float scale) 
{
	GraphicsBuffer *buffer = new GraphicsBuffer(filePath);
	mpInstance->mGBM->addBuffer("HUD", buffer);
	mHUD = new HUD(loc, buffer);
	mHUD->addAnimation(new Animation(new Sprite(buffer, loc)));
	mpInstance->mUM->addUnit(mHUD);
	mHUD->init(dataFile);
}

void Game::newFood(std::string filePath, Vector2D loc, float scale)
{
	GraphicsBuffer *buffer = new GraphicsBuffer(filePath);
	mpInstance->mGBM->addBuffer("food", buffer);
	mfFood = new Food(buffer);
	mfFood->addAnimation(new Animation(new Sprite(buffer, loc)));
	mpInstance->mUM->addUnit(mfFood);
}

void Game::newWall(std::string filePath, Vector2D loc, float scale) 
{
	GraphicsBuffer *buffer = new GraphicsBuffer(filePath);
	Unit *wall = new Unit(loc, new Animation(new Sprite(buffer, Vector2D(0, 0))));
	//wall->addAnimation(new Animation(new Sprite(buffer, loc)));
	mpInstance->mGBM->addBuffer("wall", buffer);
	mpInstance->mUM->addUnit(wall);
	mpInstance->mWalls.push_back(wall);
}

void Game::checkFoodCol() 
{
	if (mSnake->checkForFood(mfFood->getLocation())) 
	{
		mSnake->addBody();
		do {
			mfFood->newLocation();
		} while (checkWallPos(mfFood->getLocation()));

		mHUD->addScore();
	}
}

void Game::checkSnakeWall() 
{
	for (int i = 0; i < mWalls.size()-1; i++) 
	{
		mSnake->checkForWall(mWalls[i]->getLocation());
	}
}

void Game::checkSnakeLive() {

	mHUD->changeTypeUI(mSnake->snakeLive());
	if (mSnake->snakeLive()) {
		
	}
}

void Game::checkSnakeSize() 
{
	if (mSnake->getSnakeSize() > 15) {
		mSnake->resetSnake();
		nextLevel();
	}
}

void Game::loadLevel(std::string filePath) 
{
	mpInstance->mLM->LoadLevel(filePath);
}

void Game::createWalls()
{
	Level curLevel = mpInstance->mLM->getLevel(mpInstance->currentLevel);
	for (int i = 0; i < curLevel.getSize(); i++)
	{
		newWall(mpInstance->mSpritePath, curLevel.getWall(i)*40, 1.0f);
	}
	mSnake->changeSpeed(curLevel.getSpeed());

}

void Game::deconstructWalls() 
{
	Level curLevel = mpInstance->mLM->getLevel(mpInstance->currentLevel);
	for (int i = 0; i < mWalls.size(); i++) 
	{
		for (int i = 0; i < mWalls.size(); i++) 
		{
			mpInstance->mUM->removeUnit(mWalls[i]->getLocation(), Vector2D(0, 0));
		}
	}
	mWalls.clear();
}

void Game::nextLevel() 
{
	if (currentLevel < 2)
	{
		deconstructWalls();
		currentLevel++;
		createWalls();
	}
}

bool Game::checkWallPos(Vector2D unitPos)
{
	for (int i = 0; i < mWalls.size(); i++) {
		if (unitPos == mWalls[i]->getLocation()) {
			return true;
		}
	}
	return false;
}