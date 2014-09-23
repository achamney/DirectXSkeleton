#include "GameEngine.h"
#include "GameApp.h"

GameEngine::GameEngine(void)
{
	this->LastRenderTime = 0;
	this->WindowPosX = 20;
	this->WindowPosY = 20;
	this->WindowWidth = 800;
	this->WindowHeight = 600;
	this->frameRate = GetTickCount();
	din = NULL; 
	dinKeyboard = NULL;	// a pointer to a a handle to the keyboard device
	dinMouse = NULL;		// a pointer to a a handle to the mouse device
	d3d = NULL;	// a handle to the address of the direct3d com object 
	d3dDev = NULL;	// a handle ot the address of the rendering device


}

GameEngine::~GameEngine(void)
{
	// clean up
	if (dinKeyboard != NULL) {
		dinKeyboard->Unacquire();
		dinKeyboard->Release();
		dinKeyboard = NULL;
	}
	if (dinMouse != NULL) {
		dinMouse->Unacquire();
		dinMouse->Release();
		dinMouse = NULL;
	}
	if (din != NULL) {
		din->Release();
		din = NULL;
	}
	if (d3dDev != NULL) {
		d3dDev->Release();
		d3dDev = NULL;
	}

	if (d3d != NULL) {
		d3d->Release();
		d3d = NULL;
	}

}

int GameEngine::setWindowSize(int posX, int posY, int windowWidth, int windowHeight)

{
	WindowPosX = posX;
	WindowPosY = posY;
	WindowWidth = windowWidth;
	WindowHeight = windowHeight;
	return(0);
}

int GameEngine::getKeyboardState(char keysState[256])  // the state of the 256 keyboard keys
{
	int rc = 0;
	unsigned char key = 0;


	rc = dinKeyboard->GetDeviceState(256,keysState);
	while (rc != DI_OK) {
		switch (rc) {
			case DI_OK: 
				rc = 0;
				break;
			case DIERR_INPUTLOST:
			case DIERR_NOTACQUIRED:
				dinKeyboard->Acquire();
				break;
			case E_PENDING:

				break;
			case DIERR_INVALIDPARAM:
			case DIERR_NOTINITIALIZED:
			default:
				// error has occured
				return(-1);
		}
		rc = dinKeyboard->GetDeviceState(256,keysState);
	}

	return(rc);
}



int GameEngine::getMouseState(DIMOUSESTATE *mouseState)  // the state of the mouse

{
	int rc = 0;

	// note the place holder for the required strucuture (DIMOUSESTATE) is a 
	// member variale of the class - mouseState


	rc = dinMouse->GetDeviceState(sizeof(DIMOUSESTATE), (void *) mouseState);
	while (rc != DI_OK) {
		switch (rc) {
			case DI_OK: 
				rc = 0;
				break;
			case DIERR_INPUTLOST:
			case DIERR_NOTACQUIRED:
				dinMouse->Acquire();
				break;
			case E_PENDING:

				break;
			case DIERR_INVALIDPARAM:
			case DIERR_NOTINITIALIZED:
			default:
				// error has occured
				return(-1);
		}
		rc = dinMouse->GetDeviceState(sizeof(DIMOUSESTATE), (void *) mouseState);
	}

	return(rc);

}

int GameEngine::setFramesPerSecond(int FramesPerSecond)

{
	this->FramesPerSecond = FramesPerSecond;
	this->TimePerFrame = 1000 / FramesPerSecond;

	return(0);
}
/**********************************************************************************/

int GameEngine::setGameApp(GameApp *theGame)

{

	this->theGame = theGame;
	return(0);
}

int GameEngine::InitApp(HINSTANCE hInstance, // application instance
			 WNDPROC WndProc,	  // the callback function pointer
			 LPCTSTR winClassName,// the class name to be used
			 LPCTSTR title,		  // the window title
			 int nCmdShow)	      // instruction by the os whether to show the window
{
   //HWND hWnd;
   int rc = 0;
   DWORD dwStyle;

   hInst = hInstance; // Store instance handle in our global variable

   rc = RegisterWndClass(hInstance, WndProc, winClassName);
   if (rc != 0) {
		// handle error
	   MessageBox(NULL, L"Could not register class", L"error message",MB_OK);
	   return(NULL);
   }

   dwStyle = WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL;
   hWnd = CreateWindow(winClassName, title, dwStyle, WindowPosX, WindowPosY,
      WindowWidth, WindowHeight,NULL, NULL, hInstance, NULL);

   if (hWnd != NULL) {
      ShowWindow(hWnd, nCmdShow);
	  UpdateWindow(hWnd);
   }


   return(rc);

}

int GameEngine::ExecuteMsgLoop(void)
{

    // this struct holds Windows event messages
    MSG msg;

    // Enter the infinite message loop
    while(TRUE)
    {
        // Check to see if any messages are waiting in the queue
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // If the message is WM_QUIT, exit the while loop
            if (msg.message == WM_QUIT)
                break;

            // translate keystroke messages into the right format
            TranslateMessage(&msg);
			
            // send the message to the WindowProc function
            DispatchMessage(&msg);
        }
		frameRate = GetTickCount();
		theGame->updateGameState();
		theGame->RenderFrame();
		frameRate = -(frameRate - GetTickCount());
		if(frameRate < FramesPerSecond)
			Sleep(FramesPerSecond-frameRate);
    }

    // return this part of the WM_QUIT message to Windows
    return msg.wParam;

}

int GameEngine::initd3d(void)		
{ 
	int rc = 0;;
	D3DPRESENT_PARAMETERS d3dpp;

	if (d3d != NULL) return(0);	// check if the com object was already initialized

	// initialize the com object
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL) return(NULL);



	// initial the direct3D9 presenttion parameters
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	
	d3dpp.BackBufferWidth = WindowWidth;		// the width of the back buffer
	d3dpp.BackBufferHeight = WindowHeight;		// the height of the back buffer
	d3dpp.Windowed = TRUE;	
	//d3dpp.Windowed = FALSE;				// using windowed version
	d3dpp.hDeviceWindow = hWnd;			// pass the handle to the window
	//d3dpp.BackBufferFormat  = D3DFMT_R5G6B5; 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;  
	//d3dpp.Flags = NULL;// discard old frames
	//d3dpp.EnableAutoDepthStencil = TRUE ;		// enable depth
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;



	// create a directx device which will enable drawing on the screen.
	rc = d3d->CreateDevice(D3DADAPTER_DEFAULT,		// this is the main adapter
							D3DDEVTYPE_HAL,			// use hardware abstraction layer
							hWnd,					// the window to be rendered
							D3DCREATE_SOFTWARE_VERTEXPROCESSING,
							&d3dpp,					// address of the d3d parameters structures (may be modified by directx if number of backgound surfaces cannot be allocated
							&d3dDev);				// address of the allocated device

	if (rc != S_OK) {
		// release d3d (the com object
	}

	return(rc);
}

int GameEngine::initDirectInput(void)

{ 

	int rc = 0;;

	din = NULL;
	dinKeyboard = NULL;
	dinMouse = NULL;
	DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **) &din,NULL);
	if (din == NULL) {
		// could not obtain the com interface
		rc = -1;
		goto err;
	}

	// get the keyboard interface
	rc = din->CreateDevice(GUID_SysKeyboard,	// the default keyboard id
							&dinKeyboard,			// use hardware abstraction layer
							NULL);					// address of the allocated device

	if (rc != S_OK) {
		rc = -2;
		goto err;
	}


	// set up the cooperation level 
	dinKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	// set data format

	dinKeyboard->SetDataFormat(&c_dfDIKeyboard);
	


	// set the mouse interface
	rc = din->CreateDevice(GUID_SysMouse,	// the default keyboard id
							&dinMouse,			// use hardware abstraction layer
							NULL);					// address of the allocated device

	if (rc != DI_OK) {
		rc = -3;
		goto err;
	}

	// set up the cooperation level 
	rc = dinMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	if (rc != DI_OK) {
		rc = -3;
		goto err;
	}

	// set data format

	rc = dinMouse->SetDataFormat(&c_dfDIMouse);
	if (rc != DI_OK) {
		rc = -3;
		goto err;
	}


	
err:
	if (dinKeyboard == NULL) {
		dinKeyboard->Release();
	}
	if (dinMouse == NULL) {
		dinMouse->Release();
	}

	if (din == NULL) {
		din->Release();
	}

	return(rc);
}

int GameEngine::RegisterWndClass(HINSTANCE hInstance,  // the application instance
						  WNDPROC WndProc,		// the function to be attached to the main window 
						  LPCTSTR winClassName) // the class name to be used
{
	WNDCLASS wc;	// the windows class structure
	int rc = 0;

	wc.style		= CS_HREDRAW | CS_VREDRAW;	// redraw behaviour attribtes
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hInstance	= hInstance;				// application instance associated with the winwos class
	wc.hCursor		= LoadCursor(NULL, IDC_ARROW);// the cursor type of the window
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1); // the background colour of the window client area
	wc.lpszMenuName	= NULL;						// no menu 
	wc.lpfnWndProc	= WndProc;					// the callback window procedure
	wc.lpszClassName= winClassName;				// the class name which links the window with the call back function
	wc.hIcon = NULL;							// an icon of the class (NULL tells the system to use the default)

	if (RegisterClass(&wc) == 0) {
		rc = 1;
	}
	
	return(rc);
}
