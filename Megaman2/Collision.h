#pragma once
#include "gamePicture.h"

class Collision
{
public:
	Collision(void);
	static bool widthHeight(gamePicture* badassobject1,gamePicture* badassobject2);
	~Collision(void);
	static int fourcolide(gamePicture* badassobject1,gamePicture* badassobject2);
};
