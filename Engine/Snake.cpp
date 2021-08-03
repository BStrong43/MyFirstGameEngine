#include "Snake.h"

Snake::Snake(Vector2D loc, GraphicsBuffer *buffer) {
	mLocation = loc;
	mBuffer = buffer;
	mdeltaTime = 0.0f;
	mWaitTime = 300.0f;
	createHead();
	addBody();
}

Snake::~Snake() 
{
	for (int i = 0; (unsigned)i < mTail.size(); i++) {
		delete mTail[i];
	}
}

void Snake::createHead() 
{
	Unit *head = new Unit(mLocation, new Animation(new Sprite(this->mBuffer, Vector2D(0, 0))));
	head->addAnimation(new Animation(new Sprite(mBuffer, mLocation)));
	mTail.push_back(head);
}

void Snake::addBody() 
{
	Unit *tailPart = new Unit(lastLoc, new Animation(new Sprite(this->mBuffer, Vector2D(0,0))));
	mTail.push_back(tailPart);
}

void Snake::draw(System *system) 
{
	for (int i = 0; (unsigned)i < mTail.size(); i++)
	{
		system->render(mTail[i]->getLocation(), mTail[i]->getAnimation()->getCurrentSprite());
	}
}

void Snake::update(float deltaTime) 
{
	mdeltaTime += deltaTime;
	lastLoc = mTail[mTail.size()-1]->getLocation();

	if (mdeltaTime >= mWaitTime && isDead == false) {
		//Update Head
		switch (direc) {
		case UP:
			mLocation.setY(mLocation.getY() - 40);
			mTail[0]->setLocation(mLocation);
			break;

		case DOWN:
			mLocation.setY(mLocation.getY() + 40);
			mTail[0]->setLocation(mLocation);
			break;

		case LEFT:
			mLocation.setX(mLocation.getX() - 40);
			mTail[0]->setLocation(mLocation);
			break;

		case RIGHT:
			mLocation.setX(mLocation.getX() + 40);
			mTail[0]->setLocation(mLocation);
			break;
		}
		
		mdeltaTime = 0;

		//Update Tail
		if (mTail.size()>1) {
		//Once addBody() is written this loop will be tested
			for (int i = mTail.size()-1; i > 0; i--) {
				mTail[i]->setLocation(mTail[i - 1]->getLocation());
			}
			checkCollision();
		}
		
	}
}

void Snake::resetSnake() {
	//Clear tail
	/*for (int i = 1; (unsigned)i < mTail.size()-1; i++) {
		delete mTail[i];
	}*/

	mTail.clear();

	mLocation = Vector2D(0, 0);
	createHead();
	mTail[0]->setLocation(mLocation);
	lastLoc = mLocation;
	addBody();
	direc = DOWN;
	isDead = false;
}

void Snake::changeSpeed(float speed) {
	mWaitTime = speed;
}

void Snake::changeDirection(int direction) 
{
	//std::cout << "\n\n\n" << direction << "\n\n\n"; //DEBUGGING LINE
	
	//MOVE UP
	if (direction == 1) {
		if (direc != DOWN) {
			direc = UP;
		}
	}
	//MOVE DOWN
	if (direction == 3) {
		if (direc != UP) {
			direc = DOWN;
		}
	}
	//TURN LEFT
	if (direction == 2) {
		if (direc != RIGHT) {
			direc = LEFT;
		}
	}

	if (direction == 4) {
		if (direc != LEFT) {
			direc = RIGHT;
		}
	}
}

void Snake::checkCollision() 
{
	if (mLocation.getX() < 0 || mLocation.getX()>760) {
		isDead = true;
		return;
	}

	if (mLocation.getY() < 0 || mLocation.getY() > 520) {
		isDead = true;
		return;
	}
	
	for (int i = 2; (unsigned)i < mTail.size(); i++) {
		if (mLocation == mTail[i]->getLocation()) {
			isDead = true;
			return;
		}
	}
}

bool Snake::checkForFood(Vector2D foodLoc) {
	if (foodLoc == mTail[0]->getLocation()) {
		return true;
	}
	
	return false;
}

void Snake::checkForWall(Vector2D wallLoc) {
	if (wallLoc == mTail[0]->getLocation()) {
		isDead = true;
	}
}