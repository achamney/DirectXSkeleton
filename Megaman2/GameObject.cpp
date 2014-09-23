

#define GAME_GRAPHIC_OBJECT_CLASS_VARIABLE 1

#include "GameObject.h"

float GameObject::regionWidth = 0;	//the width of the region in which rocks can travel
float GameObject::regionHeight = 0;	//the width of the region in which rocks can travel



int GameObject::render(LPDIRECT3DDEVICE9 d3dDevice)
{
	
	return 0;
}

 /**************************************************************************/
GameObject::GameObject(D3DXVECTOR3 stuff)
{

}

GameObject::~GameObject(void)

{

}

int GameObject::updateState(int time)
{
	
	return 0;
}

// sets the dimensions of the region in which the rocks can travel
int GameObject::setRegionSize(float width, float height)
{
	regionWidth = width;
	regionHeight = height;

	return 0;
}

// processes the key
int GameObject::processKeys(unsigned char key)
{

	return 0;
}
