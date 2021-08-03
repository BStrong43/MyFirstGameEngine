#pragma once
#include "Level.h"
#include <fstream>

class LevelManager
{
public:
	//Constructors
	LevelManager();
	~LevelManager();

	//Utilities
	void LoadLevel(std::string filePath);
	void cleanup();

	//Accessors
	Level getLevel(int i) { return levels[i]; }
	int getNumofLevels() { return levels.size(); }

private:
	std::vector<Level> levels;
};