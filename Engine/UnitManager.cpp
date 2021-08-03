#include "UnitManager.h"

using namespace std;

UnitManager::UnitManager(System* system)
{
	mpSystem = system;
}

void UnitManager::addUnit(Unit* ut)
{
	mUnits.push_back(ut);
}

void UnitManager::removeUnit(Vector2D pos, Vector2D size)
{
	//Go throught the list backwards and find a unit to delete if it is clicked on
	for (size_t i = mUnits.size() - 1; i > 0; i--)
	{
		if (pos.getX() >= mUnits[i]->getLocation().getX() && pos.getX() <= mUnits[i]->getLocation().getX() + size.getX())
			if(pos.getY() >= mUnits[i]->getLocation().getY() && pos.getY() <= mUnits[i]->getLocation().getY() + size.getY())
			{
				Unit* temp = mUnits[i];
				mUnits.erase(mUnits.begin() + i);
				delete temp;
				return;
			}
	}
}

Unit* UnitManager::getUnit(int num)
{
	//Gets a unit using its index
	if ((unsigned)num < mUnits.size() && num >= 0)
		return mUnits[num];
	else
	{
		cout << "Unit index invalid" << endl;
		return NULL;
	}
}

Unit* UnitManager::getLastUnit()
{
	return mUnits[mUnits.size() - 1];
}

void UnitManager::update(float deltaTime)
{
	for (size_t i = 0; i < mUnits.size(); i++)
	{
		mUnits[i]->update(deltaTime);
	}
}

void UnitManager::draw()
{
	for (size_t i = 0; i < mUnits.size(); i++)
	{
		mUnits[i]->draw(mpSystem);
	}
}

void UnitManager::clear()
{
	for (size_t i = 0; i < mUnits.size(); i++)
	{
		delete mUnits[i];
	}
}

void UnitManager::pauseAll()
{
	//Pause the units that are running, unpause the animations that arent.
	for (int i = 0; (unsigned)i < mUnits.size(); i++)
	{
		mUnits[i]->getAnimation()->pauseAnimation();
		mUnits[i]->changeAnimation();
		mUnits[i]->getAnimation()->pauseAnimation();
		mUnits[i]->changeAnimation();
	}
}

void UnitManager::handleEvent(const Event& theEvent) 
{
	if (theEvent.getType() == CHANGE_ANIM) 
	{
		getLastUnit()->changeAnimation();
	}

	if (theEvent.getType() == PAUSE_EVENT) 
	{
		pauseAll();
	}
}