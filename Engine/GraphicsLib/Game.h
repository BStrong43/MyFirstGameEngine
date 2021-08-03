#pragma once
#include "System.h"
#include "Unit.h"
#include <vector>


class Game : public Trackable {
public:
	Game(int width = 800, int height = 600);
	~Game();

	void init();
	void cleanUp();

	void doLoop();

	void addSprite(int width, int height, Vector2D loc);
	void addSprite(std::string path, Vector2D loc);
	void addSpriteSheet(std::string path, Vector2D loc, Vector2D dimensions);
	void addAnimation(int unitIndex, std::string path, Vector2D dimensions);

private:
	System* mSystem;
	int mWidth, mHeight;
	std::vector<Unit*> units;
	std::vector<GraphicsBuffer* > buffers;

	bool isRunning = false;
	bool enterPressed = false;
	bool fPressed = false;
	bool sPressed = false;
	bool escPressed = false;

	void update(float timePass);
	void draw();
	void processInput();
};