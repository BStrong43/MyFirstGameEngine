#pragma once
#include <Vector2D.h>
#include "Animation.h"
#include "System.h"
#include <vector>

class Unit : public Trackable 
{
public:
	Unit(Vector2D loc, Animation* anim, float scale = 1.0f);
	Unit() {}
	~Unit();

	virtual void draw(System* system);
	virtual void update(float timePassed);
	void changeAnimation();
	void addAnimation(Animation* anim) { mAnims.push_back(anim); }
	Vector2D getLocation() { return mLocation; }
	void setLocation(Vector2D loc) { mLocation = loc; }
	void changeAnimationSpeed(float speed);
	Animation* getAnimation() { return mAnims[currentAnimation]; }
private:
	Vector2D mLocation;
	std::vector<Animation*> mAnims;
	int currentAnimation;
	float mScale = 1.0f;
};