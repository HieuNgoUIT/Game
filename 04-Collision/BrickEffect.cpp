#include "BrickEffect.h"


BrickEffect::~BrickEffect()
{
}

BrickEffect::BrickEffect()
{
	_texture = new Texture("Resource\\sprites\\Effect\\brick.png", 1, 1, 1);
	_sprite = new Sprite(_texture, 100);
	isVisible = false;
	isDoneRender = false;

}



void BrickEffect::Update(DWORD dt, int direction)
{
	vx = 0.05f*direction;
	vy = 0.4f;
	dx = vx * dt;
	dy = vy * dt;
	x += dx;
	y += dy;

}

void BrickEffect::Render(Camera* camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	_sprite->Draw(pos.x, pos.y);
	//CGameObject::RenderBoundingBox();
}
