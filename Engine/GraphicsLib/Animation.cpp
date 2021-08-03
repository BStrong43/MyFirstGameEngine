#include "Animation.h"

Animation::Animation(Sprite* sprite, float delay) 
{
	mAnim.push_back(sprite);
	mDelay = delay;
	mCurrentSprite = mAnim[0];
	mLoc = sprite->getLocation();
}

Animation::Animation(float delay)
{
	mDelay = delay;
}

//deletes all of the animations
Animation::~Animation() 
{
	for (size_t i = 0; i < mAnim.size();i++) 
	{
		delete mAnim[i];
	}

}

//Updates the animation and loops back to the beginning if needed
void Animation::update(float deltaTime)
{
	if (shouldLoop)
	{
		time += deltaTime;
		if (mDelay <= time)
		{
			if (mCurrentSprite == mAnim[mAnim.size() - 1])
			{
				mCurrentSprite = mAnim[0];
			}
			else
			{
				mCurrentSprite = mAnim[getIndexOfAnimation() + 1];
			}
			time = 0;
	}
}
}

void Animation::addSpriteToAnimation(Sprite* sprite) 
{
	mAnim.push_back(sprite);
}  

//returns the index of the animation within a vector
int Animation::getIndexOfAnimation()
{
	for (size_t i = 0; i < mAnim.size(); i++)
	{
		if (mAnim[i] == mCurrentSprite)
			return i;
	}
}

//Changes the speed. Max of 60 times a second and no limit on how slow it can go 
void Animation::changeSpeed(float speed) 
{
	mDelay += speed;
	if (mDelay < 0.0f)
		mDelay = 0.0f;
}

void Animation::pauseAnimation()
{
	if (shouldLoop)
		shouldLoop = false;
	else
		shouldLoop = true;
}
