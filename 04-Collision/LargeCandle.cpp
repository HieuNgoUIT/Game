#include "LargeCandle.h"



LargeCandle::LargeCandle(int X, int Y, int numberItem)
{
	_texture = new Texture("Resource\\sprites\\Ground\\0.png", 2, 1, 2);
	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	tag = 10;
	itemNumber = numberItem;
	itemLink = ConvertItemNumbertoString(itemNumber);
	
	item = new Item();
	
}
void LargeCandle::RenderBoundingBox(Camera * camera)
{
	CGameObject::RenderBoundingBox(camera);
}
char * LargeCandle::ConvertItemNumbertoString(int number)
{
	switch (number)
	{
	case 2:
		return "Resource\\sprites\\Items\\BIG_HEART.png";
		break;	
	case 8:
		return "Resource\\sprites\\Items\\MORNING_STAR.png";
		break;
	case 14:
		return "Resource\\sprites\\Items\\KNIFE.png";
		break;
	default:
		break;
	}
	
}
LargeCandle::LargeCandle()
{
}


LargeCandle::~LargeCandle()
{
}
void LargeCandle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (!isDead)
	{
		left = x;
		top = y;
		right = x + _texture->FrameWidth;
		bottom = y + _texture->FrameHeight;
	}


}

void LargeCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void LargeCandle::Render(Camera * camera)
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

void LargeCandle::Delete()
{
	delete _texture;
	delete _sprite;
}