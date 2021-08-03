#pragma once
#include "Unit.h"

enum Directions : int {
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};

class Snake : public Unit {
public :
	//Constructors
	Snake() {};
	Snake(Vector2D loc, GraphicsBuffer *buffer);
	~Snake();

	//Utilities
	virtual void draw(System *system);
	virtual void update(float timePassed);
	void addBody();
	void checkCollision();
	bool checkForFood(Vector2D foodLoc);
	void checkForWall(Vector2D wallLoc);
	void resetSnake();
	
	//Accessors
	Vector2D getPositionofUnit(int index = 0) { return mTail[index]->getLocation(); }
	bool snakeLive() { return isDead; }
	int getSnakeSize() { return mTail.size(); }
	
	//Mutators
	void changeDirection(int direc);
	void changeSpeed(float speed);

	virtual Animation* getAnimation() { return NULL; };
	

private:
	void createHead();

	Directions direc = DOWN;
	Vector2D mLocation;
	Vector2D lastLoc;
	GraphicsBuffer *mBuffer;
	std::vector<Unit*> mTail;
	float mdeltaTime, mWaitTime, scale = 1.0f;
	bool isDead = true;

};