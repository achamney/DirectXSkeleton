#include "GameApp.h"

GameApp::GameApp(void)
{
}

GameApp::~GameApp(void)
{
	gameEngine.~GameEngine();
}

// initializes the game
int GameApp::setFramesPerSecond(int FramesPerSecond)
{

	gameEngine.setFramesPerSecond(FramesPerSecond);

	return 0;
}






