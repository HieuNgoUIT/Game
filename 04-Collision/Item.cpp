#include "Item.h"

Item::Item(int X, int Y)
{
	char* path = PathRandom();
	_texture = new Texture(path, 1, 1, 1);
	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	tag = 69;
}
char* Item::PathRandom()
{
	int randomNumber = rand() % 13;
	switch (randomNumber)
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
	default:
		break;
	}
}
Item::Item()
{
}

Item::~Item()
{
}

void Item::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isDead)
	{
		CGameObject::Update(dt);
		vy += 0.005 * dt;
		y += dy;
		if (y > 370)
			y = 370;
		//_sprite->Update(dt); // update animation

	}
}
void Item::RenderBoundingBox(Camera * camera)
{
	CGameObject::RenderBoundingBox(camera);
}
void Item::Render(Camera * camera)
{
	if (!isDead)
	{
		D3DXVECTOR2 pos = camera->Transform(x, y);
		_sprite->Draw(pos.x, pos.y);
		RenderBoundingBox(camera);
	}
}

int Item::GetIsCreated()
{
	return isCreated;
}
