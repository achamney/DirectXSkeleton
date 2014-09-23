#include "Collision.h"

Collision::Collision(void)
{

}

bool Collision::widthHeight(gamePicture* badassobject1 ,gamePicture* badassobject2)
{
	bool collision = false;
	int bottom1 = badassobject1->picheight/2 + badassobject1->position.y;
	int bottom2 = badassobject2->picheight/2 + badassobject2->position.y;
	int top1 = -badassobject1->picheight/2 + badassobject1->position.y;
	int top2 = -badassobject2->picheight/2 + badassobject2->position.y;
	int left1 = -badassobject1->picwidth/2 + badassobject1->position.x;
	int left2 = -badassobject2->picwidth/2 + badassobject2->position.x;
	int right1 = badassobject1->picwidth/2 + badassobject1->position.x;
	int right2 = badassobject2->picwidth/2 + badassobject2->position.x;
	
	if (bottom1 >= top2)
	{

		if(top1 <= bottom2)
		{

			if (left1 <= right2)
			{
				if (right1 >= left2)
				{
					collision = true;
				}
			}
		}
	}

	if (collision == true)
	{
		return true;
	}
}

int Collision::fourcolide(gamePicture* badassobject1,gamePicture* badassobject2) //1 = megaman 2 = box
{
	int bottom1 = badassobject1->picheight/2 + badassobject1->position.y;
	int bottom2 = badassobject2->picheight/2 + badassobject2->position.y;
	int top1 = -badassobject1->picheight/2 + badassobject1->position.y;
	int top2 = -badassobject2->picheight/2 + badassobject2->position.y;
	int left1 = -badassobject1->picwidth/2 + badassobject1->position.x + badassobject1->vel.x;
	int left2 = -badassobject2->picwidth/2 + badassobject2->position.x;
	int right1 = badassobject1->picwidth/2 + badassobject1->position.x + badassobject1->vel.x;
	int right2 = badassobject2->picwidth/2 + badassobject2->position.x;
	int boxsize = 20 + abs (badassobject1->vel.x/2);

	if (bottom1 > top2)
	{

		if(top1 < bottom2)
		{
			if(right1 > left2)								//4colide starts
			{
				if(right1 < left2 + boxsize)
					return 4;
			}

			if(left1 < right2)								
			{
				if(left1 > right2 - boxsize)
					return 2;
			}																					
		}
	}                                                       //ends
	
	if (left1 < right2)									
	{
		if (right1 > left2)                                //starts
		{
			if (top1 <= bottom2)
			{
				if (top1 >= bottom2 - boxsize)
					return 3;
			}	
				if(bottom1 + badassobject1->vel.y >= top2)
				{
					if (bottom1 + badassobject1->vel.y <= top2 + boxsize)
						return 1;
				}
															//ends
		}
	}
	return 0;
}

Collision::~Collision(void)
{
}
