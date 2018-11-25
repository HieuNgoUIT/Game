#include "HiddenStair.h"

HiddenStair::~HiddenStair()
{
}
HiddenStair::HiddenStair(int X,int Y)
{
	_texture = new Texture("Resource\\sprites\\Ground\\NULL.png", 1, 1, 1);
	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	this->tag = 7;
}

void HiddenStair::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

void HiddenStair::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void HiddenStair::Render(Camera * camera)
{
	CGameObject::RenderBoundingBox(camera);
}

void HiddenStair::RenderBoundingBox(Camera * camera)
{
	CGameObject::RenderBoundingBox(camera);
}
