#include "TheMegaMan.h"

TheMegaMan::TheMegaMan(D3DXVECTOR3 seed,LPDIRECT3DDEVICE9 d3dDev, D3DXVECTOR2 cCount):gamePicture(seed,d3dDev,cCount)
{
	size /= 3;
	picwidth = 175/3;
	picheight = 200/3;
	keysl = false;
	keysr = false;
	keysz = false;

}
int TheMegaMan::processKeys(unsigned char key)
{
	speedcap = 10;

	if (key == DIK_LEFT) 
	{
		speedcap = -10;
		if(vel.x <= speedcap)
		{
			vel.x = speedcap;
		}
		vel.x -= 2;
		cellPosition.x -= cellSize.x;
		cellPosition.y = cellSize.y;
		keysl = true;
	}

	if (key == DIK_RIGHT)
	{
		speedcap = 10;
		if(vel.x >= speedcap)
		{
			vel.x = speedcap;
		}
		vel.x += 2;
		cellPosition.x += cellSize.x;
		cellPosition.y = 0;
		keysr = true;
	}

	if (key == DIK_UP) 
	{
		if(nojumping == false)
		{
			vel.y -= 20;
		}
		nojumping = true;
	}

		if (key == DIK_Z)
	{
		speedcap = 100000000;
		if(vel.x >= speedcap)
		{
			vel.x = speedcap;
		}
		vel.x += 2;
		cellPosition.x += cellSize.x;
		cellPosition.y = 0;
		keysz = true;
	}

		if (key == DIK_B) 
	{
		this->~TheMegaMan();

	}

	/*if (key == DIK_DOWN)
	{
		cellPosition.x += cellSize.x;
		cellPosition.y = 0;
		this->position.y += 1;
	}*/

	return 0;
}

int TheMegaMan::dprocessKeys(unsigned char key)
{
	if(key == DIK_LEFT&&keysl == true)
	{
		keysl = false;
	}

	else if(key == DIK_RIGHT && keysr == true)
	{
		keysr = false;
	}
	if (key == DIK_Z && keysz == true)
	{
		keysz = false;
	}
	if(keysl == false&&keysr == false&&keysz == false)
	{
		vel.x/=1.2f;
	}
	return 0;
}

int TheMegaMan::render(LPDIRECT3DDEVICE9 d3dDev)
{
	d3dDev->SetTexture(0, this->curTexture);
	gamePicture::render(d3dDev);
	return 0;
}
int TheMegaMan::update(void)
{
	this->position.y += vel.y;
	this->vel.y += 1;
	return 0; 
}

TheMegaMan::~TheMegaMan(void)
{
}
