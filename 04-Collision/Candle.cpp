#include "Candle.h"

Candle::Candle(int X, int Y, int numberItem)
{
	_texture = new Texture("Resource\\sprites\\Ground\\1.png", 2, 1, 2);
	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	tag =11;
	itemNumber = numberItem;
	itemLink = ConvertItemNumbertoString(itemNumber);

	item = new Item();
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

char * Candle::ConvertItemNumbertoString(int number)
{
	switch (number)
	{
	case 1:
		return "Resource\\sprites\\Items\\13.png";
		break;
	case 2:
		return "Resource\\sprites\\Items\\BIG_HEART.png";
		break;
	case 3:
		return "Resource\\sprites\\Items\\DOUBLE_SHOT.png";
		break;
	case 4:
		return "Resource\\sprites\\Items\\INVICIBILITY_ITEM.png";
		break;
	case 5:
		return "Resource\\sprites\\Items\\Money_bag_blue.png";
		break;
	case 6:
		return "Resource\\sprites\\Items\\Money_bag_red.png";
		break;
	case 7:
		return "Resource\\sprites\\Items\\Money_bag_white.png";
		break;
	case 8:
		return "Resource\\sprites\\Items\\MORNING_STAR.png";
		break;
	case 9:
		return "Resource\\sprites\\Items\\ROAST.png";
		break;
	case 10:
		return "Resource\\sprites\\Items\\ROSARY.png";
		break;
	case 11:
		return "Resource\\sprites\\Items\\SMALL_HEART.png";
		break;
	case 12:
		return "Resource\\sprites\\Items\\STOP_WATCH.png";
		break;
	case 13:
		return "Resource\\sprites\\Items\\TRIPLE_SHOT.png";
		break;
	case 14:
		return "Resource\\sprites\\Items\\KNIFE.png";
		break;
	case 15:
		return "Resource\\sprites\\Items\\HOLY_WATER.png";
		break;
	case 16:
		return "Resource\\sprites\\Items\\AXE.png";
		break;
	default:
		break;
	}
}
