#include "Unit.h"


Unit::Unit(Vector2D loc, Animation* anim, float scale) 
{
	mLocation = loc;
	mAnims.push_back(anim);
	currentAnimation = 0;
	mScale = scale;
}
Unit::~Unit() 
{
	for (size_t i = 0; i < mAnims.size();i++)
		delete mAnims[i];
	mAnims.clear();
}

void Unit::draw(System* system) 
{
	Sprite temp = *getAnimation()->getCurrentSprite();
	system->mGraphicsSystem->draw(mLocation, &temp, mScale);
	
}
void Unit::update(float timePassed)
{
	getAnimation()->update(timePassed);
}

void Unit::changeAnimation() 
{
	currentAnimation = ++currentAnimation % mAnims.size();
	mAnims[currentAnimation]; 
}	

void Unit::changeAnimationSpeed(float speed) 
{
	for(size_t i = 1; i < mAnims.size(); i++)
		mAnims[i]->changeSpeed(speed);
}