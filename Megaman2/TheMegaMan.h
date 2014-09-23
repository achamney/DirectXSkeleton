#pragma once
#include "gamepicture.h"

class TheMegaMan :
	public gamePicture
{
public:
	TheMegaMan(D3DXVECTOR3 seed,LPDIRECT3DDEVICE9 d3dDev, D3DXVECTOR2 cCount);
	~TheMegaMan(void);
	int render(LPDIRECT3DDEVICE9 d3dDev);
	int processKeys(unsigned char key);
	int update(void);
	bool nojumping;
	int speedcap;
	bool keysl;
	bool keysr;
	bool keysz;
	int dprocessKeys(unsigned char key);
};
