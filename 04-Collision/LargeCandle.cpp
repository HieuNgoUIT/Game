#include "LargeCandle.h"



LargeCandle::LargeCandle(int X,int Y)
{
	_texture = new Texture("Resource\\sprites\\Ground\\0.png", 2, 1, 2);
	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	tag = 41;
	health = 1;
	id = 161;
	item = new Item();
}
void LargeCandle::RenderBoundingBox(Camera * camera)
{
	CGameObject::RenderBoundingBox(camera);
}
LargeCandle::LargeCandle()
{
}


LargeCandle::~LargeCandle()
{
}
void LargeCandle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;

}

void LargeCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isDead)
	{
		_sprite->Update(dt); // update animation
	}
	if (isDead && isCreated==0)
	{
		dropItem = 1;
		isCreated = 1;
		//isCreated = 1;
		//item->isCreated = 1;
	}	
}

void LargeCandle::Render(Camera * camera)
{
	if (!isDead)
	{
		D3DXVECTOR2 pos = camera->Transform(x, y);
		_sprite->Draw(pos.x, pos.y);
		RenderBoundingBox(camera);
	}
	/*if(item->GetIsCreated() ==1)
	{
		item->Render(camera);
	}*/
	
}

void LargeCandle::Delete() 
{
	delete _texture;
	delete _sprite;
}