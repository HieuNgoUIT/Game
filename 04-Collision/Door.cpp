#include "Door.h"

Door::Door(int TYPE,int X,int Y)
{
	//_texture = new Texture("Resource\\sprites\\Ground\\door2.bmp", 3, 1, 3);
	//_sprite = new Sprite(_texture, 1000);
	texId = TYPE;
	tag = TYPE;
	this->x = X;
	this->y = Y;
	//isDead = false;
}

Door::~Door()
{
}

void Door::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (!isDead)
	{
		left = x;
		top = y;
		right = x + _texture->FrameWidth ;
		bottom = y + _texture->FrameHeight;
	}
	
}

void Door::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//_sprite->SelectIndex(0);
	_sprite->Update(dt);
}

void Door::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	_sprite->Draw(pos.x, pos.y);
	RenderBoundingBox(camera);
}

void Door::RenderBoundingBox(Camera * camera)
{
	CGameObject::RenderBoundingBox(camera);
}
