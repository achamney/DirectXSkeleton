#pragma once
#include "gamePicture.h"
#include<vector>
#include "TheMegaMan.h"

using std::vector;
class Background : public gamePicture
{
public:
	Background(LPDIRECT3DDEVICE9 d3dDev);
	Background(D3DXVECTOR3 seed, LPDIRECT3DDEVICE9 d3dDev, D3DXVECTOR2 cCount);
	~Background(void);
	int render(LPDIRECT3DDEVICE9 d3dDev);
	void update(TheMegaMan*);
};
