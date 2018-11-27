#include "Door.h"

Door::Door(int X,int Y)
{
	_texture = new Texture("Resource\\sprites\\Ground\\door2.bmp", 3, 1, 3);
	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
}

Door::~Door()
{
}

void Door::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
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
