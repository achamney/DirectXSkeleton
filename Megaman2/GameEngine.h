#pragma once
#include <windows.h>
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
//#include <windowsx.h>

#include "d3d9.h"
#include "d3dX9.h"
#include "dinput.h"


//#include "GameApp.h"

class GameApp;

class GameEngine
{
private:
	// members
	time_t LastRenderTime;   // the time that the last rendering took place
	int FramesPerSecond;		// refersh rate of game
	time_t TimePerFrame;
	GameApp *theGame;			// the game application
	
	int WindowPosX, WindowPosY;
	int WindowWidth, WindowHeight;




public:
	HINSTANCE hInst;		// the game instance
	HWND hWnd;				// the game window
	LPDIRECTINPUT8 din;	// a pointer to a handle to the direct input com object 
	LPDIRECTINPUTDEVICE8 dinKeyboard;	// a pointer to a a handle to the keyboard device
	LPDIRECTINPUTDEVICE8 dinMouse;		// a pointer to a a handle to the mouse device
	LPDIRECT3D9 d3d;	// a handle to the address of the direct3d com object 
	LPDIRECT3DDEVICE9 d3dDev;	// a handle ot the address of the rendering device
	int frameRate;

	// functions and procedures

public:
	GameEngine(void);
	~GameEngine(void);

	int setGameApp(GameApp *theGame);
	int setWindowSize(int posX, int posY, int windowWidth, int windowHeight);
	int setFramesPerSecond(int FramesPerSecond);

	int InitApp(HINSTANCE hInstance, // application instance
			 WNDPROC WndProc,	  // the callback function pointer
			 LPCTSTR winClassName,// the class name to be used
			 LPCTSTR title,		  // the window title
			 int nCmdShow);	      // instruction by the os whether to show the window

	int ExecuteMsgLoop(void);
	int initd3d(void);			

	int initDirectInput(void);			
	int getKeyboardState(char keysState[256]);			
	int getMouseState(DIMOUSESTATE *mouseState);			


	int RegisterWndClass(HINSTANCE hInstance,  // the application instance
						  WNDPROC WndProc,		// the function to be attached to the main window 
						  LPCTSTR winClassName); // the class name to be used

};
