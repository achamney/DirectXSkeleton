#pragma once



#include "GameObject.h"
#include "GameApp.h"
#include "gamePicture.h"
#include "Background.h"
#include "TheMegaMan.h"
#include "Block.h"
//#include<vector>
// The custom FVF
// initial window position and size
#define WINDOW_POS_X 30
#define WINDOW_POS_Y 30

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700

// processing speed
#define FRAMES_PER_SECOND 30

// storage size
#define QAUD_ROCKS_BUF_SIZE 1000
#define SPRITE_ROCKS_BUF_SIZE 1000
#define ROCKETS_BUF_SIZE 10
#define BULLETS_BUF_SIZE 30000

/******************************************************************************************/


class MegaMan : public GameApp
{
public:
	MegaMan();
	//Asteroid(LPDIRECT3DDEVICE9 d3dDevice);
	~MegaMan(void);

public:

public:
	int MegaMan::RenderFrame(void);
 
	int InitGame(HINSTANCE hInstance, // application instance
			 WNDPROC WndProc);	  // the callback function pointer


	int playGame();		// play the game
	// updates the state of the game
	int updateGameState(void);
	
	// creates the game objects
	int createGameObjects(int numRockets);

private:
	int numBullets;	// counts the number of rocks in the game
	// input data structures
	char keysState[256];				// the state of the 256 keyboard keys
	DIMOUSESTATE mouseState;	// the state of the mouse
	TheMegaMan* megaman;
	Background* inthecity;
	Background* theotherone;
	
	// procsesses the keyboard input from the user
	int processKeyboardInput(void);
	int processMouseInput(void);
	static vector<gamePicture*> objs;

	// initializa the game
	int initGame(void);

};


