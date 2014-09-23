#pragma once
#include "gamepicture.h"
#include "TheMegaMan.h"
#include "Collision.h"

class Block :
	public gamePicture
{
public:
	Block(D3DXVECTOR3 seed,LPDIRECT3DDEVICE9 d3dDev, D3DXVECTOR2 cCount, int type);
	int render(LPDIRECT3DDEVICE9 d3dDev);
	static int renderAll(LPDIRECT3DDEVICE9 d3dDev);
	void update(TheMegaMan* megaman);
	static void updateAll(TheMegaMan* megaman);
	static vector<Block*> blockList;
	static void createLevel(LPDIRECT3DDEVICE9 d3dDev);
	int type;
	enum { scenery, boost, health, normal, wall, inception, kaboom};
	~Block(void);
};
