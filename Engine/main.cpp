/*
Author: Ben Strong
Class: 310-02
Assignment: Assignment 5
Certification of Authenticity: All assignment 4 code has been used with permission from Richard Hardy in section 310-02.
All assignment 5 code is my own
*/

#include <iostream>
#include <cassert>
#include <string>
#include <iostream>
#include <fstream>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "GraphicsLib.h"
#include "Game.h"
#include <time.h>

using namespace std;

int main()
{

	const string ASSET_PATH = "Assets\\";

	fstream file;
	file.open(ASSET_PATH + "maindata.txt", std::ios::in);

	//File Names
	string SNAKE_FILENAME;// = "snake_square.png";
	string FOOD_FILENAME;// = "pickup.png";
	string BACKGROUND_FILENAME;// = "steps.png";
	string HUD_FILENAME;// = "HUD.png";
	string FONT_FILENAME;// = "cour.ttf";
	string GROUND_FILENAME;// = "ground.png";
	string LEVEL_ONE;
	string LEVEL_TWO;
	string LEVEL_THREE;

	getline(file, SNAKE_FILENAME);
	getline(file, FOOD_FILENAME);
	getline(file, BACKGROUND_FILENAME);
	getline(file, HUD_FILENAME);
	getline(file, FONT_FILENAME);
	getline(file, GROUND_FILENAME);
	getline(file, LEVEL_ONE);
	getline(file, LEVEL_TWO);
	getline(file, LEVEL_THREE);

	Vector2D woodsLocation(-100,0);
	Vector2D spriteLocation(0, 0);
	Vector2D spriteDimensions(60, 60);
	Vector2D HUDLocation(0, 560);

	EventSystem::init();
	EventSystem* eventSystem = EventSystem::getInstance();
	
	Game::init(eventSystem, ASSET_PATH + GROUND_FILENAME);
	Game* pGame = Game::getInstance();
	
	//added background
	pGame->addSprite(ASSET_PATH + BACKGROUND_FILENAME, woodsLocation, "woods", 1.0f);

	//Added the snake
	pGame->newSnake(ASSET_PATH + SNAKE_FILENAME, spriteLocation);

	//Load Levels
	pGame->loadLevel(ASSET_PATH + LEVEL_ONE);
	pGame->loadLevel(ASSET_PATH + LEVEL_TWO);
	pGame->loadLevel(ASSET_PATH + LEVEL_THREE);
	pGame->loadLevel(ASSET_PATH + LEVEL_THREE);

	//Create first level
	pGame->createWalls();

	//Added the Food
	pGame->newFood(ASSET_PATH + FOOD_FILENAME, Vector2D(0, 0));

	//Added HUD
	pGame->newHUD(ASSET_PATH + HUD_FILENAME, ASSET_PATH + FONT_FILENAME, HUDLocation);

	//Starts the game loop
	pGame->doLoop();

	//Clean up
	pGame->cleanUp();

	file.close();

	gMemoryTracker.reportAllocations(cout);

	cout << "Press a button to conitue...";
	cin.get();

	return 0;
}