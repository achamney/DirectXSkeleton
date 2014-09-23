#pragma once

/**************************************************************************************/
//INCLUDE

#include "GameObject.h"

#include<vector>

using std::vector;
/**************************************************************************************/
//STRUCTURES
struct RocketVertex {
    D3DXVECTOR3 pos;	// the position in space
	float rhw;			// The transformed position for the vertex
    DWORD color;        // The vertex color
	float tu, tv;		//Robbie edit: For textures
};

/**************************************************************************************/
// GLOBALS

/**************************************************************************************/
/* PROTOTYPES */


/**************************************************************************************/
// DEFINE

#define ROCKET_NUM_VTX  20


#define D3DFVF_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)


/******************************************************************************************/





class gamePicture : public GameObject
{
public:
	gamePicture(LPDIRECT3DDEVICE9 d3dDev);
	//gamePicture(D3DXVECTOR3 seed, LPDIRECT3DDEVICE9 d3dDev);
	gamePicture(D3DXVECTOR3 seed, LPDIRECT3DDEVICE9 d3dDev, D3DXVECTOR2 cCount);
	gamePicture(D3DXVECTOR3 stuff);
	int updateRotation(D3DXVECTOR3& mouseVector);
	~gamePicture(void);
	int updateRotation(POINT* p);
	virtual int render(LPDIRECT3DDEVICE9 d3dDev);
	virtual int initGeom(D3DXVECTOR3 seed,LPDIRECT3DDEVICE9 d3dDev);
	virtual int updateState(int time);
	static void setTextures(LPDIRECT3DDEVICE9 d3dDevice);
	D3DXVECTOR3 getVel();
	static vector<IDirect3DTexture9*> textureList; 
	IDirect3DTexture9* curTexture;
	int picheight;
	int picwidth;

protected:


	// the vertex geometry of hte object
	struct RocketVertex vtx[ROCKET_NUM_VTX];
	struct RocketVertex vtx2[ROCKET_NUM_VTX];
	LPDIRECT3DVERTEXBUFFER9 pVtxBuf; // Buffer to hold vertices

public:

	float speed;
	D3DXVECTOR3 navVector;

public:
	D3DXVECTOR2 cellCount; 
	D3DXVECTOR2 cellSize;
	D3DXVECTOR2 cellPosition;
	D3DXVECTOR2 size;
	int updateHeading(float deltaHeading);
	int updateVelocity(float acc);
};

