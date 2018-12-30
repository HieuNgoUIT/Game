#include "CheckPoint.h"

CheckPoint::CheckPoint()
{
	_texture = new Texture("Resource\\sprites\\Ground\\NULL.png",1, 1,1);
	_sprite = new Sprite(_texture, 100);
	//x = X;
	//y = Y;
}

CheckPoint::~CheckPoint()
{
}

void CheckPoint::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

void CheckPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void CheckPoint::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	_sprite->Draw(pos.x, pos.y);
	RenderBoundingBox(camera);
}

void CheckPoint::RenderBoundingBox(Camera * camera)
{
	CGameObject::RenderBoundingBox(camera);
}
