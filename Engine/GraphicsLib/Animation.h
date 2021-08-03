#pragma once
#include "Sprite.h"
#include <vector>

class Animation : public Trackable 
{
public:
	Animation(Sprite* sprite, float delay = 50.1f);
	Animation(float delay = 50.1f);
	Animation() {}
	~Animation();

	void update(float deltaTime);
	Sprite* getCurrentSprite(){ return mCurrentSprite; };
	void setCurrentSprite(int index) { mCurrentSprite = mAnim[index]; }
	void changeSpeed(float speed);
	float getSpeed() { return mDelay; }
	void addSpriteToAnimation(Sprite* sprite);

	void pauseAnimation();


private:
	bool shouldLoop = true;
	std::vector<Sprite*> mAnim;
	Vector2D mLoc;
	float mDelay;
	Sprite* mCurrentSprite;
	float time = 0;
	int getIndexOfAnimation();
};