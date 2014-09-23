
// include the basic windows header file


#include <windows.h>
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
//#include <windowsx.h>

#include "d3d9.h"
#include "d3dX9.h"

#include "MegaMan.h"


int RegisterClass(HINSTANCE hInstance, LPCWSTR wndTitle, LPCWSTR wndClassName);
HWND InitInstance(HINSTANCE hInstance, LPCWSTR  wndClassName, LPCWSTR wndTitle, int nCmdShow);
int ExecuteMsgLoop(void);
HWND InitApp(HINSTANCE hInstance, WNDPROC WndProc, LPCTSTR winClassName, LPCTSTR title, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

LPDIRECT3D9 initd3d(LPDIRECT3D9 *d3d, LPDIRECT3DDEVICE9 *device, HWND hWnd);
int initDirectInput(LPDIRECTINPUT8 *din, LPDIRECTINPUTDEVICE8 *dinKeyboard,
					LPDIRECTINPUTDEVICE8 *dinMouse,	HINSTANCE hinstance,HWND hwnd);

HINSTANCE hInst;								// current instance


LPDIRECT3D9 d3d;


// the directx device
LPDIRECT3DDEVICE9 d3dDevice;

#define D3DFVF_MYVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)


#define ANIMATE_BACKGROUND 0

int WINAPI WinMain(HINSTANCE hInstance,
				HINSTANCE hPrevInstance,
				PSTR    lpCmdLine,
				int       nCmdShow)
{

	int rc = 0;
//	D3DXVECTOR3 seed;
	// get a new game
	MegaMan theGame;
	rc = theGame.InitGame(hInstance, WndProc);
	if (rc != 0) {
		return(1);
	}
	
	// play the game
	rc = theGame.playGame();
	return(rc);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int rc = 1;
	
    // sort through and find what code to run for the message given
    switch(message)
    {
        // this message is read when the window is closed
        case WM_DESTROY:
            
				//rc = MessageBox(NULL, L"this was invoked from the window procedure", L"Inside Window Procedure",MB_OKCANCEL);
                // close the application entirely
				PostQuitMessage(0);
				return 0;
             break;

		case WM_CREATE:
			rc = SendMessage(hWnd,WM_SETICON,ICON_SMALL,(LPARAM)LoadIcon(NULL, TEXT("../textures/Game.ico")));
			break;
			
    }

    // Handle any messages the switch statement didn't
	
    return DefWindowProc (hWnd, message, wParam, lParam);
}






