#include "FireBall.h"

FireBall::FireBall(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Enemies\\FIREBALL.png", 1, 1, 1);
	_sprite = new Sprite(_texture, 200);
	this->x = X;
	this->y = Y;
	health = 10;
	tag = 500;
}

FireBall::~FireBall()
{
}

void FireBall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (health > 0)
	{
		left = x;
		top = y;
		right = x + _texture->FrameWidth;
		bottom = y + _texture->FrameHeight;
	}
}

void FireBall::Update(DWORD dt, float simonx, vector<LPGAMEOBJECT>* coObjects)
{
	if (health > 0)
	{
		vx = 0.09f;
		CGameObject::Update(dt);
		x += dx;
	}
}

void FireBall::Render(Camera * camera)
{
	if (health > 0)
	{
		D3DXVECTOR2 pos = camera->Transform(x, y);
		_sprite->Draw(pos.x, pos.y);
		CGameObject::RenderBoundingBox(camera);
	}
	
}
