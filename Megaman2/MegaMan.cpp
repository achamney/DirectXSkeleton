#include "MegaMan.h"
int shapeSpawnTime = 0;
int shapeSpawnTimeMax = 100;
vector<gamePicture*> MegaMan::objs;
MegaMan::MegaMan()
{
}
MegaMan::~MegaMan(void)
{
}

int MegaMan::initGame()
{
	int numRockets = 1;
	int rc = 0;
	
	
	if (gameEngine.d3dDev == NULL) return(-1);

	// create objects
	rc = createGameObjects(numRockets);
	if (rc != 0) {
		rc = -1;
		goto err;
	}

	// set the region for the rocks and the rocket in order to allow wrap around
	rc = GameObject::setRegionSize((float) WINDOW_WIDTH, (float) WINDOW_HEIGHT);
	if (rc != 0) {
		rc = -2;
		goto err;
	}

err:
	return(rc);
}

int MegaMan::updateGameState(void)
{	
	Block::updateAll(megaman);
	inthecity->update(megaman);
	theotherone->update(megaman);

	processKeyboardInput();
	
	int j;
	
	processMouseInput();
	megaman->update();
	
	return 0;
}
 // renders all objects
int MegaMan::RenderFrame(void)
{
    // clear the window to a deep blue
	gameEngine.d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    gameEngine.d3dDev->BeginScene();    // begins the 3D scene
	megaman->orient += 0;
	for(int i=0;i<objs.size();i++)
	{
		gamePicture* temp = objs.at(i);
		temp->render(gameEngine.d3dDev);
	}
	Block::renderAll(gameEngine.d3dDev);
	//rocket->location.x += 1;
	// render the QuadRocks

    gameEngine.d3dDev->EndScene();    // ends the 3D scene

    gameEngine.d3dDev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
	megaman->updateState(0);
	 return 0;
 }


/**************************************************************************/


// creates the game objects


int MegaMan::createGameObjects(int numRockets)
{
	int rc = 0;
	D3DXVECTOR3 seed;

	gamePicture::setTextures(gameEngine.d3dDev);
	srand(clock());
	D3DXVECTOR3 vec(199,176,0);
	
	inthecity = new Background(vec,this->gameEngine.d3dDev,D3DXVECTOR2(1,1));
	objs.push_back(inthecity);
	theotherone = new Background(vec,this->gameEngine.d3dDev,D3DXVECTOR2(1,1));
	objs.push_back(theotherone);
	megaman = new TheMegaMan(vec,this->gameEngine.d3dDev,D3DXVECTOR2(11,5));
	objs.push_back(megaman);
megaman = new TheMegaMan(vec,this->gameEngine.d3dDev,D3DXVECTOR2(11,5));
	objs.push_back(megaman);
	objs.push_back(megaman);
	objs.push_back(megaman);

	theotherone ->position.x = 3600; 
	Block::createLevel(gameEngine.d3dDev);
	//rocket = new gamePicture(vec,this->gameEngine.d3dDev);
	//rocket->initGeom(vec,gameEngine.d3dDev); 
	megaman->orient = 0;
	// create 1st rocket in the middle of the window/screen
	seed.x = WINDOW_WIDTH / 2;
	seed.y = WINDOW_HEIGHT / 2;
	seed.z = 0.9f;

	if (seed.x > WINDOW_WIDTH) {
		seed.x = seed.y / 2;
		seed.y += 100;
	}
	 return(rc);
 }

int MegaMan::processKeyboardInput(void)
{

	//unsigned char key = '0';

	// get the keyboard array from the game engine
	char keys[256]; 
	//rc=gameEngine.dinKeyboard->GetDeviceState(256,keys)

	gameEngine.getKeyboardState(keys);

	// process the data
	/*if (keys[DIK_ESCAPE] & 0x80) 
		rocket->processKeys(DIK_ESCAPE);
	// check which of the four arrow keys was pressed
	
	// check if left arrow key (if so call the rocket to process it)
	*/if (keys[DIK_LEFT] & 0x80) 
		megaman->processKeys(DIK_LEFT);
	else megaman->dprocessKeys(DIK_LEFT);

	// check if right arrow key (if so call the rocket to process it)
	  if (keys[DIK_RIGHT] & 0x80) 
		megaman->processKeys(DIK_RIGHT);
	  else megaman->dprocessKeys(DIK_RIGHT);
	
	// check if up arrow key (if so call the rocket to process it)
	if (keys[DIK_UP] & 0x80) 
		megaman->processKeys(DIK_UP);	
	
	// check if down arrow key (if so call the rocket to process it)
	if (keys[DIK_DOWN] & 0x80) 
		megaman->processKeys(DIK_DOWN);

	if (keys[DIK_Z] & 0x80) 
		megaman->processKeys(DIK_Z);
	else megaman->dprocessKeys(DIK_Z);

	if (keys[DIK_B] & 0x80) 
		megaman->processKeys(DIK_B);
	else megaman->dprocessKeys(DIK_B);

	return 0;
}



/**************************************************************************/



// procsesses the mouse input from the user
int MegaMan::processMouseInput(void)
{
	int rc = 0;

	rc = gameEngine.getMouseState(&this->mouseState);
	POINT point; // a point structure
	GetCursorPos(&point); // get absolute cursor position
	ScreenToClient(gameEngine.hWnd, &point); // convert to position relative to the window
	RECT rect; // a rect structure
	GetClientRect(gameEngine.hWnd, &rect); // get our rect coordinates
/*	if (point.x >= rect.left && point.x <= rect.right &&
		point.y >= rect.top && point.y <= rect.bottom && mouseState.rgbButtons[0] & 0x80)
	{
		rocket->updateRotation(&point);
		
	}
*/	
	return 0;
}



/**********************************************************************************/

 int MegaMan::InitGame(HINSTANCE hInstance, // application instance
					  WNDPROC WndProc)	  // the callback function pointer


{
   int rc = 0;

   // set game window sizeWINDOW_POS_X 30

   gameEngine.setWindowSize(WINDOW_POS_X, WINDOW_POS_Y, WINDOW_WIDTH, WINDOW_HEIGHT);
   gameEngine.setFramesPerSecond(FRAMES_PER_SECOND);
   gameEngine.setGameApp(this);
   rc = gameEngine.InitApp(hInstance, WndProc, L"asteroid_game",L"MegaMan", 1);	

 /*  gameEngine.initd3d(&d3d, &d3dDevice, hWnd);
   rc = gameEngine.initDirectInput(&din, &dinKeyboard, &dinMouse, hInstance,hWnd);*/
   gameEngine.initd3d();
   rc = gameEngine.initDirectInput();


   // init the game objects
	initGame();

   return(rc);

}

/**********************************************************************************/

 int MegaMan::playGame()		// play the game

 {

    int rc = 0;

    // execute the main message loop
	rc = gameEngine.ExecuteMsgLoop();


   return(rc);

}
