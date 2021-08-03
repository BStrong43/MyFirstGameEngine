#include "Level.h"

Vector2D Level::getWall(int i)
{
	return walls[i];
}

void Level::addWall(int i, int j)
{
	walls.push_back(Vector2D(i, j));
}