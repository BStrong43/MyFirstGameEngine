#pragma once

#include <Vector2D.h>
#include "Unit.h"
#include "Animation.h"
#include "System.h"
#include <vector>
#include "System.h"
#include "EventSystem.h"
#include "EventListener.h"
#include "Event.h"

class UnitManager : public EventListener
{
public:
	UnitManager(System* system);
	~UnitManager() { EventSystem::getInstance()->removeListenerFromAllEvents(this); };
	

	void addUnit(Unit* ut);
	void removeUnit(Vector2D pos, Vector2D size);
	Unit* getUnit(int num);
	Unit* getLastUnit();

	void update(float deltaTime);
	void draw();
	void clear();

	void pauseAll();
	virtual void handleEvent(const Event& theEvent);

private:
	std::vector<Unit*> mUnits;
	System* mpSystem;
};