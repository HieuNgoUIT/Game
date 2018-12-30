#include "Candle.h"

Candle::Candle(int TYPE,int X, int Y, int numberItem)
{
//	_texture = new Texture("Resource\\sprites\\Ground\\1.png", 2, 1, 2);
//	_sprite = new Sprite(_texture, 100);
	texId = TYPE;
	this->x = X;
	this->y = Y;
	tag =11;
	itemNumber = numberItem;
	
}

Candle::~Candle()
{
}

void Candle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (!isDead)
	{
		left = x;
		top = y;
		right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
	}
}

void Candle::Update(DWORD dt, float simonx , vector<LPGAMEOBJECT>* coObjects)
{

	if (!isDead)
	{
		_sprite->Update(dt); // update animation
	}
	else
	{
		CGameObject::UpdateEffect(dt);
	}
	if (isDead && isCreated == 0)
	{
		dropItem = 1;
		isCreated = 1;
		//isCreated = 1;
		//item->isCreated = 1;
	}
}

void Candle::Render(Camera * camera)
{
	if (!isDead)
	{
		D3DXVECTOR2 pos = camera->Transform(x, y);
		_sprite->Draw(pos.x, pos.y);
		RenderBoundingBox(camera);
	}
	else
	{
		CGameObject::RenderEffect(camera);
	}
}


