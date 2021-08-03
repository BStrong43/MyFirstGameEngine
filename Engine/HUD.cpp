#include "HUD.h"

HUD::HUD(Vector2D loc, GraphicsBuffer *buffer) 
{
	mLocation = loc;
	mBuffer = buffer;
	mColor = new Color();
	//init();
}

HUD::~HUD() {
	delete mBuffer, drawnBuffer, mFont, mColor;
}

void HUD::update(float timePassed)
{
	if (!isDeathUI) {
		mText = "Score: " + std::to_string(score) + " FPS: " + mFPS;
	}
	if (isDeathUI) {
		mText = "You Died | Press Enter to Play Again!";
	}
}

void HUD::init(std::string filePath) 
{
	mFont = new Font(20, filePath);
}

void HUD::draw(System *system) 
{
	drawnBuffer = mBuffer;
	system->getGraphicsSystem()->writeText(drawnBuffer, Vector2D(400,20) , mFont, mColor, mText);
	system->render(mLocation, new Sprite(drawnBuffer, Vector2D(0, 0)));
	system->getGraphicsSystem()->drawColor(drawnBuffer, mColor);
}

std::string HUD::calculateFPS(float timePassed) 
{
	float fps = 1000 / timePassed;
	return std::to_string(fps);
}

void HUD::checkFPS(float timePassed) {
	mFPS = "FPS: " + calculateFPS(timePassed);
}

void HUD::changeTypeUI(bool isDead) 
{
	isDeathUI = isDead;
}