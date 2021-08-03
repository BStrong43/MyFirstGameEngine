#include "Unit.h"


Unit::Unit(Vector2D loc, Animation* anim) 
{
	mLocation = loc;
	mAnims.push_back(anim);
	currentAnimation = 0;
}
Unit::~Unit() 
{
	for (int i = 0; i < mAnims.size();i++)
		delete mAnims[i];
	mAnims.clear();
}

void Unit::draw(System* system) 
{
	Sprite temp = *getAnimation()->getCurrentSprite();
	system->mGameSystem->draw(temp.getBitmap(), mLocation, &temp, 1.0f);
	system->mGameSystem->draw(mLocation, &temp, 1.0f);
}
void Unit::update(float timePassed) {
	getAnimation()->update(timePassed);
}

void Unit::changeAnimation() 
{
	currentAnimation = ++currentAnimation % mAnims.size();
	mAnims[currentAnimation]; 
}