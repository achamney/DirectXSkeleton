#include "Block.h"

vector<Block*> Block::blockList;

Block::Block(D3DXVECTOR3 position,LPDIRECT3DDEVICE9 d3dDev, D3DXVECTOR2 cCount, int atype):gamePicture(position,d3dDev,cCount)
{
	curTexture = gamePicture::textureList[0];
	size /= 5;
	picwidth = 200/5;
	picheight = 200/5;
	type = atype;
}

int Block::render(LPDIRECT3DDEVICE9 d3dDev)
{
	d3dDev->SetTexture(0, this->curTexture);
	gamePicture::render(d3dDev);
	return 0;
}
int Block::renderAll(LPDIRECT3DDEVICE9 d3dDev)
{
	for (int i = 0; i<blockList.size(); i++)
	{	
		blockList[i]->render(d3dDev);
	}

	return 0;
}

void Block::createLevel(LPDIRECT3DDEVICE9 d3dDev)
{
	D3DXVECTOR2 cCount = D3DXVECTOR2 (1,1);              
	for (int j = 0; j < 5; j++)                          //creates floor only 
	{
		for (int i = 0; i < 100; i++) 
		{
			if (j > 0) 
			{
				D3DXVECTOR3 position = D3DXVECTOR3(0 + i*40,600 + j*40,0);
				blockList.push_back(new Block(position, d3dDev, cCount, scenery));
			}
			if (j == 0)
			{
			    D3DXVECTOR3 position = D3DXVECTOR3(0 + i*40,600 + j*40,0);
				blockList.push_back(new Block(position, d3dDev, cCount, normal));
			} 
		} 
	}

	for (int j = 0; j < 18; j++)                          //creates wall only 
	{
		for (int i = 0; i < 3; i++) 
		{
			D3DXVECTOR3 position = D3DXVECTOR3(-120 + i*40,680 - j*40,0);
			blockList.push_back(new Block(position, d3dDev, cCount, wall));

			position = D3DXVECTOR3(4000 + i*40,680 - j*40,0);
			blockList.push_back(new Block(position, d3dDev, cCount, wall));
		} 
	}
}

void Block::update(TheMegaMan* megaman)
{
	position.x -= megaman->vel.x;
}

void Block::updateAll(TheMegaMan* megaman)
{
	for (int i = 0;i < blockList.size();i++)
	{
		if(blockList[i]->type != scenery)
		{
		int call;
		call = Collision::fourcolide(megaman,blockList[i]);
			

		if (call == 1)
		{
			if (blockList[i]->type == normal)
			{
				int blocktop = -blockList[i]->picheight/2 + blockList[i]->position.y;
				megaman->position.y = blocktop - megaman->picheight/2;
				megaman->vel= D3DXVECTOR3(megaman->vel.x,0,0); //->~TheMegaMan() = funny hahaha!!!
				megaman->nojumping = false;
			}
		}
		if (call == 3)
		{
			int blockbottom = blockList[i]->picheight/2 + blockList[i]->position.y;
			megaman->position.y = blockbottom + megaman->picheight/2+1;
			megaman->vel= D3DXVECTOR3(megaman->vel.x,0,0); //->~TheMegaMan() = funny hahaha!!!
		}
		if (call == 2)
		{
			megaman->vel= D3DXVECTOR3(0,megaman->vel.y,0); //->~TheMegaMan() = funny hahaha!!!
		}
		if (call == 4)
		{
			megaman->vel= D3DXVECTOR3(0,megaman->vel.y,0); //->~TheMegaMan() = funny hahaha!!!
		}
		}
	}
	for (int i = 0; i < blockList.size();i++)
	{
			blockList[i]->update(megaman);
	}
}

Block::~Block(void)
{
}
