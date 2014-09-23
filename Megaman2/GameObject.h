#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "d3d9.h"
#include "d3dx9.h"
#include "dinput.h"

struct vertex {
    D3DXVECTOR3 pos;	// the position in space
	float rhw;			// The transformed position for the vertex
    DWORD color;        // The vertex color
};

struct Point {
	int x;
	int y;
};

class GameObject
{

public:
	// counts the number of objects that were created

protected:
			// the locaton in space
					// the orientation in space
	D3DXVECTOR3 dir;			// direction of motion  (nuss make it redundant)
				// velocity vector;  at every time step (every 1Hz)
	D3DXVECTOR3 acc;			// accelaration vector;  at every time step (every 1Hz)
	float rotationStep;			// change in rotation at every time step (every 1Hz)


	//static variables
	//static LPDIRECT3DDEVICE9 d3dDevice; // the directd3d device for drawing the objects


	static float regionWidth;	//the width of the region in which rocks can travel
	static float regionHeight;	//the width of the region in which rocks can travel




public:
	//GameObject(void){numObjects++;};
	float orient;
	D3DXVECTOR3 position;
	D3DXVECTOR3 vel;
	GameObject(D3DXVECTOR3 stuff);
	virtual ~GameObject(void);
	bool colliding;
	int rotSpeed;
	float mass;
	GameObject* lastCollider;
	// render the object.  This is a virutal function so that each object will render it self
	virtual int render(LPDIRECT3DDEVICE9 d3dDevice);
	virtual int updateState(int time);
	// adds a rocket to the rendering list
	//int addRocket(GameObject &go);


	// Static functcions declaration.
//	static void setd3dSprite(LPD3DXSPRITE d3dSprite);//{	GameObject::d3dSprite = d3dSprite;};
	
	// Static functcions declaration.
//	static void setd3dDevice(LPDIRECT3DDEVICE9 d3dDevice);
	// renders objects
//	static int RenderObjects(GameObject **buf, int NumObjects);
	static int setRegionSize(float width, float height);


	//static LPD3DXSPRITE d3dSprite;
//	static LPD3DXSPRITE d3dSprite;

	// responds to the key stroke
	virtual int processKeys(unsigned char key);



};


#ifndef GAME_GRAPHIC_OBJECT_CLASS_VARIABLE

//extern int GameObject::numObjects;

#endif


