#pragma once
#include <Vector2D.h>
#include "Animation.h"
#include "System.h"
#include <vector>

class Unit : public Trackable {
public:
	Unit(Vector2D loc, Animation* anim);
	Unit() {}
	~Unit();

	void draw(System* system);
	void update(float timePassed);
	void changeAnimation();
	void addAnimation(Animation* anim) { mAnims.push_back(anim); }
	Vector2D getLocation() { return mLocation; }
	Animation* getAnimation() { return mAnims[currentAnimation]; }
private:
	Vector2D mLocation;
	std::vector<Animation*> mAnims;
	int currentAnimation;
};