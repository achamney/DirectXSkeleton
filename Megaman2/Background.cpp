#include "Background.h"


Background::Background(LPDIRECT3DDEVICE9 d3dDev): gamePicture(d3dDev)
{
	orient;
}
Background::Background(D3DXVECTOR3 seed, LPDIRECT3DDEVICE9 d3dDev, D3DXVECTOR2 cCount): gamePicture(seed, d3dDev, cCount)
{
	curTexture = textureList[3];
	position = D3DXVECTOR3(1200,400,0);
	orient = 0;
	size = D3DXVECTOR2(12,7);
}
int Background::render(LPDIRECT3DDEVICE9 d3dDev)
{
	d3dDev->SetTexture(0, this->curTexture);
	gamePicture::render(d3dDev);
	return 0;
}
void Background::update(TheMegaMan* megaman)
{	
	if (position.x < -1200)
	{
		position.x += 4800;
	}
	position.x -= megaman->vel.x;
		if (position.x > 3600)
	{
		position.x -= 4800;
	}
}
Background::~Background(void)
{
}
