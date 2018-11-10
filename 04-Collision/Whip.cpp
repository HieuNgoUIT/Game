#include "Whip.h"

Whip::Whip(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Weapons\\VAMPIRE_KILLER.png", 3, 1, 3);
	_sprite = new Sprite(_texture, 100);
	x = X;
	y = Y;
	tag = 2;
	health = 1;
}

Whip::Whip()
{
}

Whip::~Whip()
{
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	_sprite->Update(dt);
	//CGameObject::Update(dt);
	
}

void Whip::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	_sprite->Draw(pos.x, pos.y);
}
