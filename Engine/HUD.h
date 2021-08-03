#pragma once
#include "Unit.h"

class HUD : public Unit {
public:
	//CONSTRUCTORS
	HUD(Vector2D loc, GraphicsBuffer *buffer);
	~HUD();

	//Utilities
	void update(float timePassed);
	void draw(System *system);
	void init(std::string filePath);
	std::string calculateFPS(float timePassed);
	void changeTypeUI(bool isDead);

	//Mutators
	void addScore(int bonus = 1000) { score += bonus; }
	void resetScore() { score = 0; }
	void changeText(std::string newText) { mText = newText; }
	void checkFPS(float timePassed);


private:
	Vector2D mLocation;
	GraphicsBuffer *mBuffer, *drawnBuffer;
	Font *mFont;
	Color *mColor;
	int score;
	bool isDeathUI = true;
	std::string mText = "Press Enter to Start";
	std::string mFPS;
};
