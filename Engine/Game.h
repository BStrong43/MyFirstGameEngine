#pragma once

#include "System.h"
#include <vector>
#include "UnitManager.h"
#include "GraphicsBufferManager.h"
#include "LevelManager.h"
#include "InputTranslator.h"
#include "EventSystem.h"
#include "EventListener.h"
#include "Snake.h"
#include "HUD.h"
#include "Food.h"


class Game : public EventListener {
public:
	static Game* getInstance();

	static void init(EventSystem *eventSystem, std::string groundPath);
	static void cleanUp();

	void doLoop();

	void addSprite(int width, int height, Vector2D loc, std::string buffname, float scale = 1.0f);
	void addSprite(std::string path, Vector2D loc, std::string buffname, float scale = 1.0f);
	void addSpriteSheet(std::string path, Vector2D loc, Vector2D dimensions, std::string buffname, float scale = 1.0f);
	void addAnimation(int unitIndex, std::string path, Vector2D dimensions, std::string buffname);

	void newUnit(GraphicsBuffer* buffOne, GraphicsBuffer* buffTwo, Vector2D loc, Vector2D dimensions, float scale = 1.0f);
	void newSnake(std::string filePath, Vector2D loc, float scale = 1.0f);
	void newHUD(std::string filePath, std::string dataFile, Vector2D loc, float scale = 1.0f);
	void newFood(std::string filePath, Vector2D loc, float scale = 1.0f);
	void newWall(std::string filePath, Vector2D loc, float scale = 1.0f);
	
	void checkFoodCol();
	void checkSnakeSize();
	void checkSnakeLive();
	void checkSnakeWall();
	bool checkWallPos(Vector2D unitLoc);
	void loadLevel(std::string filePath);
	void nextLevel();
	void createWalls();
	void deconstructWalls();
	
	virtual void handleEvent(const Event& theEvent);

private:
	static Game* mpInstance;

	Game(EventSystem *eventSystem, int width = 800, int height = 600);
	~Game();
	int currentLevel = 0;
	Snake *mSnake;
	HUD *mHUD;
	Food *mfFood;
	std::vector<Unit*> mWalls;

	EventSystem *mEventSystem;
	InputTranslator *mTranslator;
	System* mSystem;
	int mWidth, mHeight;

	GraphicsBufferManager* mGBM;
	UnitManager* mUM;
	LevelManager *mLM;

	Vector2D mSpriteSize = Vector2D(60, 60);

	std::string mSnakeName = "snake";
	std::string mItemName = "deans";
	std::string mBGName = "woods";
	std::string mfFoodName = "food";
	std::string mHUDName = "HUD";
	std::string mWallName = "wall";
	std::string mSpritePath;

	bool mIsRunning = false;

	void update(float timePass);
	void draw();
	void processInput();
};