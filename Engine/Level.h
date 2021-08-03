#pragma once
#include "Unit.h"

class Level 
{
public:
	//Constructors
	Level() {}

	//Mutators
	void addWall(int i, int j);
	void addWall(Vector2D newWall) { walls.push_back(newWall); }
	void setSpeed(float newSpeed) { speed = newSpeed; }

	//Accessors
	Vector2D getWall(int i);
	int getSize() { return walls.size(); }
	float getSpeed() { return speed; }

private:
	std::vector<Vector2D> walls;
	float speed = 300;
};