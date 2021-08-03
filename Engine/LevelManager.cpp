#include "LevelManager.h"

LevelManager::LevelManager() 
{
}

LevelManager::~LevelManager() 
{

}

void LevelManager::LoadLevel(std::string filePath) 
{
	
	Level newLevel = Level();
	std::fstream file;
	file.open(filePath, std::ios::in);

	if (!file.bad())
	{
		std::cout << "bad\n";


		for (int i = 0; i < 14; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				char space;
				file >> space;
				if (space == 'X')
				{
					newLevel.addWall(j, i);
				}
			}
		}

		float newSpeed;
		file >> newSpeed;
		newLevel.setSpeed(newSpeed);

		levels.push_back(newLevel);
	}
	file.close();
}

void LevelManager::cleanup() 
{
	levels.clear();
}