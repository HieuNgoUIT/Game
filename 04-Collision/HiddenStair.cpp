#include "HiddenStair.h"

HiddenStair::~HiddenStair()
{
}
HiddenStair::HiddenStair(int TYPE,int X,int Y,int direction,int isLeft)
{
	_texture = new Texture("Resource\\sprites\\Ground\\NULL.png", 1, 1, 1);
	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	this->tag = TYPE;
	this->direction = direction;
	this->isLeft = isLeft;
}

void HiddenStair::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth-30;
	bottom = y + _texture->FrameHeight+10;
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
