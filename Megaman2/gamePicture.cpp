/**************************************************************************************/
//INCLUDE

#include "gamePicture.h"

/**************************************************************************************/
//STRUCTURES

// A structure for our custom vertex type



/**************************************************************************************/
// GLOBALS


/**************************************************************************************/
/* PROTOTYPES */


/**************************************************************************************/
// DEFINE

#define ROCKET_NUM_VTX  20
#define ROCKET_VTX 8

/******************************************************************************************/




/* 
FUNCTION()
PURPOSE: 

COMMENTS:

INPUT:

OUTPUT: 

RETURN:
0 if succesful completion


*/
vector<IDirect3DTexture9*> gamePicture::textureList;


gamePicture::gamePicture(LPDIRECT3DDEVICE9 d3dDev):GameObject(D3DXVECTOR3())
{
	
	this->pVtxBuf = NULL;
	
}
gamePicture::gamePicture(D3DXVECTOR3 stuff):GameObject(stuff)
{
	
	this->pVtxBuf = NULL;
	
}
gamePicture::gamePicture(D3DXVECTOR3 seed,LPDIRECT3DDEVICE9 d3dDev, D3DXVECTOR2 cCount):GameObject(D3DXVECTOR3())
{
	D3DXVECTOR3 vel(0,-2.0f,0);			// Start off velocity 
	D3DXVECTOR3 acc(0,0,0);
	D3DXVECTOR3 nav(0, -250.0f, 0);			// Used for rotating
	this->cellSize = D3DXVECTOR2(1,1);
	this->size = D3DXVECTOR2(1,1);
	this->pVtxBuf = NULL;
	this->cellCount = cCount;
	this->cellSize.x = 1/cCount.x;
	this->cellSize.y = 1/cCount.y;
	this->vel = vel;
	this->acc = acc;
	this->navVector = nav;
	this->orient=-90;
	this->rotationStep = 0;
	this->speed = 8;
	this->curTexture = gamePicture::textureList.at(1);
	this->cellPosition.x = 0;
	this->cellPosition.y = 0;
	this->initGeom(seed,d3dDev);

	// get the velocity vector from an initial speed
	vel.x = this->speed * cos(D3DXToRadian(this->orient));
	vel.y = this->speed * sin(D3DXToRadian(this->orient));

}



/*****************************************************************************/



gamePicture::~gamePicture(void)
{
	if (this->pVtxBuf != NULL) {
		this->pVtxBuf->Release();
	}
}


/*****************************************************************************/



int gamePicture::initGeom(D3DXVECTOR3 seed,LPDIRECT3DDEVICE9 d3dDev)
{
	int i;
    VOID* pVtx;
	int size = 10;

	position = seed;

	if (pVtxBuf != NULL) {
		pVtxBuf->Release();
	}
	// initialize the geometry
	for (i = 0; i < 4; i++) {
		vtx[i].pos.z = 0.5;
		vtx[i].rhw = 0.5;
		//vtx[i].color = D3DCOLOR_ARGB(255,255-i*80,0,  i*60);
		vtx[i].color = D3DCOLOR_ARGB(255, 255, 255, 255);
	}


	vtx[0].pos.x = -10*size;
	vtx[0].pos.y = -10*size;
	//vtx[0].color = D3DCOLOR_XRGB(0, 0, 0);
	vtx[1].pos.x = 10*size;
	vtx[1].pos.y = -10*size;
	//vtx[1].color = D3DCOLOR_XRGB(0, 0, 0);
	vtx[2].pos.x = 10*size;
	vtx[2].pos.y = 10*size;
	//vtx[2].color = D3DCOLOR_XRGB(0, 0, 0);
	vtx[3].pos.x = -10*size;
	vtx[3].pos.y = 10*size;
	//vtx[3].color = D3DCOLOR_XRGB(0, 0, 0);
	vtx[0].tu = cellPosition.x;
	vtx[0].tv = cellPosition.y;

	vtx[1].tu = cellSize.x;
	vtx[1].tv = cellPosition.y;

	vtx[2].tu = cellSize.x;
	vtx[2].tv = cellPosition.y + cellSize.y;

	vtx[3].tu = 0.0;
	vtx[3].tv = cellPosition.y + cellSize.y;
	// initialize the vertex buffer for rendering
	if( FAILED( d3dDev->CreateVertexBuffer((ROCKET_VTX) * sizeof( struct RocketVertex ),
                                                  0, D3DFVF_VERTEX,
                                                  D3DPOOL_DEFAULT, &pVtxBuf, NULL ) ) )
    {
        return E_FAIL;
    }

    // Fill the vertex buffer. To do this -  Lock() the VB to
    // gain access to the vertices. This mechanism is required becuase vertex
    // buffers may be in device memory.

    if( FAILED(pVtxBuf->Lock( 0, sizeof(RocketVertex) * (ROCKET_VTX ), ( void** )&pVtx, 0 ) ) )
        return E_FAIL;
    memcpy( pVtx, vtx, sizeof(RocketVertex) * ROCKET_VTX/2 );
//	memcpy( pVtx, navVtx, sizeof(RocketVertex) * 2);
    pVtxBuf->Unlock();

	return 0;
}



/*****************************************************************************/


int gamePicture::render(LPDIRECT3DDEVICE9 d3dDevice)
{

	struct RocketVertex *pVtx;
	static float seedx = 0.0;
	static float seedy = 0.0;
	static float step = 3;
	int i;
//	float rad;
	D3DXMATRIX matTransform, matScale, matTranslate,  matRotation;


	D3DXMatrixTranslation(&matTranslate, position.x, position.y, position.z);

	D3DXMatrixScaling(&matScale, size.x,size.y,1);
	//rad = D3DXToRadian(orient);
	D3DXMatrixRotationZ(&matRotation, D3DXToRadian(orient));
	matTransform = matScale * matRotation * matTranslate ;

    // Obtain the vertex buffer and update the coordinates
    // buffer may be in device memory.
    if( FAILED(pVtxBuf->Lock( 0, sizeof(RocketVertex) * ROCKET_VTX/2, ( void** )&pVtx, 0 ) ) )
        return E_FAIL;

	// copy the records
	memcpy( pVtx, vtx, sizeof(RocketVertex) * ROCKET_VTX/2 );
	// update the coordinates
	for (i = 0; i < ROCKET_VTX/2; i++) {
		D3DXVec3TransformCoord(&pVtx[i].pos, &vtx[i].pos, &matTransform);
	}
    pVtxBuf->Unlock();
	
	d3dDevice->SetStreamSource( 0, pVtxBuf, 0, sizeof(RocketVertex) );
    d3dDevice->SetFVF(D3DFVF_VERTEX);
	//d3dDevice->SetRenderState(D3DRS_COLORVERTEX, true);
	d3dDevice->SetRenderState(D3DRS_FOGCOLOR , D3DBLEND_ZERO);
	d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true); 
	d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); 
	//d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE); 
	//d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	d3dDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, 2 );
	d3dDevice->SetTexture(0, NULL);
   // d3dDevice->DrawPrimitive( D3DPT_LINESTRIP, 0, 3);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	

	return 0;
}


/*****************************************************************************/

// updating the rocket position in space

//Note: time is not used yet.

int gamePicture::updateState(int time)
{
	vtx[0].tu = cellPosition.x;
	vtx[0].tv = cellPosition.y;

	vtx[1].tu = cellPosition.x + cellSize.x;
	vtx[1].tv = cellPosition.y;

	vtx[2].tu = cellPosition.x + cellSize.x;
	vtx[2].tv = cellPosition.y + cellSize.y;

	vtx[3].tu = cellPosition.x ;
	vtx[3].tv = cellPosition.y + cellSize.y;

	
	//location += vel;

	if (position.x > regionWidth) {
		position.x = (position.x - regionWidth);
	} else if (position.x < 0) {
		position.x = regionWidth+position.x;
	}
	if (position.y > regionHeight) {
		position.y =  (position.y - regionHeight);
	} else if (position.y < 0) {
		position.y = regionHeight +position.y;
	}


	return 0;
}

/*****************************************************************************/
// update the heaeding of the rocket
int gamePicture::updateHeading(float deltaHeading)
{
	orient = deltaHeading;
	return 0;
}

int gamePicture::updateRotation(D3DXVECTOR3& mouseVector)
{
	//if(abs(mouseVector.x)>3&& abs(mouseVector.y)>3)
	//{

	if(mouseVector.x >0)
		orient = atan(mouseVector.y/mouseVector.x)*180/3.1415;
	else
		orient = atan(mouseVector.y/mouseVector.x)*180/3.1415+180;

	//vel.x = cos(orient*3.1415 / 180)*10;
	//vel.y = sin(orient*3.1415 / 180)*10;

	//}
	//else
	//{
	//	vel.x = 0;
	//	vel.y = 0;
	//}
	return 0;
}

int gamePicture::updateRotation(POINT* p)
{
	
	D3DXVECTOR3 mouseVector(p->x - position.x, p->y - position.y, 0); //define a vector that
	if(abs(mouseVector.x)>3&& abs(mouseVector.y)>3)
	{
		if(mouseVector.x >0)
			orient = atan(mouseVector.y/mouseVector.x)*180/3.1415;
		else
			orient = atan(mouseVector.y/mouseVector.x)*180/3.1415+180;
		vel.x = cos(orient*3.1415 / 180)*10;
		vel.y = sin(orient*3.1415 / 180)*10;
	}
	else
	{
		vel.x = 0;
		vel.y = 0;
	}
	return 0;
}
/*****************************************************************************/

// update the velocity of the rocket


int gamePicture::updateVelocity(float acc)
{
	

	return 0;
}
D3DXVECTOR3 gamePicture::getVel()
{
	return vel;
}
void gamePicture::setTextures(LPDIRECT3DDEVICE9 d3dDevice)
{
	IDirect3DTexture9* curText = NULL;
	D3DXCreateTextureFromFile(d3dDevice,L"../textures/redblock.bmp",&curText);
	gamePicture::textureList.push_back(curText);
	D3DXCreateTextureFromFile(d3dDevice,L"../textures/megs.dds",&curText);
	gamePicture::textureList.push_back(curText);
	D3DXCreateTextureFromFile(d3dDevice,L"../textures/sky.bmp",&curText);
	gamePicture::textureList.push_back(curText);
	D3DXCreateTextureFromFile(d3dDevice,L"../textures/city looped.bmp",&curText);
	gamePicture::textureList.push_back(curText);
}
