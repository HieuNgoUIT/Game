#include "Zombie.h"
#pragma once

Zombie::Zombie(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Enemies\\ZOMBIE.png", 2, 1, 2);
	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	tag = 500;//enemy from 500
	direction = -1;
	vx = 1;
}

Zombie::~Zombie()
{
}

void Zombie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (!isDead)
	{
		left = x;
		top = y;
		right = x + _texture->FrameWidth;
		bottom = y + _texture->FrameHeight;
	}
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (direction == -1)
	{
		x -= vx;
	}
	else
	{
		x += vx;
	}
	_sprite->Update(dt);
}

void Zombie::Render(Camera * camera)
{
	if (!isDead)
	{

		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (direction == -1)
			_sprite->Draw(pos.x, pos.y);
		else
			_sprite->DrawFlipX(pos.x, pos.y);
		RenderBoundingBox(camera);
	}
}
