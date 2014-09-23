#pragma once

#include "GameEngine.h"

class GameApp
{
public:
	// members
	GameEngine gameEngine;




		// functions and procuedures

public:
	GameApp(void);
	~GameApp(void);

	virtual int InitGame(HINSTANCE hInstance, // application instance
			 WNDPROC WndProc) = NULL;	  // the callback function pointer


	virtual int playGame() = NULL;


	virtual int RenderFrame(void) = NULL;
	// initializes the game
	int setFramesPerSecond(int FramesPerSecond);
	// updates the state of the game
	virtual int updateGameState(void) = NULL;
	// sets the rendering device

};
