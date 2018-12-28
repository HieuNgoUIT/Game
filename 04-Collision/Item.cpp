#include "Item.h"

//Item::Item()
//{
//	//char* path = PathRandom();
//	/*_texture = new Texture(path, 1, 1, 1);
//	_sprite = new Sprite(_texture, 100);
//	this->x = X;
//	this->y = Y;
//	remainingTime = 500;
//	if (path == HEART_PATH)
//	{
//		tag = HEART_TAG;
//	}
//	else if (path == REDBAG_PATH)
//	{
//		tag = REDBAG_TAG;
//	}
//	else if (path == BLUEBLAG_PATH)
//	{
//		tag = BLUEBLAG_TAG;
//	}*/
//
//}
//char* Item::PathRandom()
//{
//	int randomNumber = rand() % 13;
//	switch (randomNumber)
//	{
//	case 1:
//		return "Resource\\sprites\\Items\\13.png";
//		break;
//	case 2:
//		return "Resource\\sprites\\Items\\BIG_HEART.png";
//		break;
//	case 3:
//		return "Resource\\sprites\\Items\\DOUBLE_SHOT.png";
//		break;
//	case 4:
//		return "Resource\\sprites\\Items\\INVICIBILITY_ITEM.png";
//		break;
//	case 5:
//		return "Resource\\sprites\\Items\\Money_bag_blue.png";
//		break;
//	case 6:
//		return "Resource\\sprites\\Items\\Money_bag_red.png";
//		break;
//	case 7:
//		return "Resource\\sprites\\Items\\Money_bag_white.png";
//		break;
//	case 8:
//		return "Resource\\sprites\\Items\\MORNING_STAR.png";
//		break;
//	case 9:
//		return "Resource\\sprites\\Items\\ROAST.png";
//		break;
//	case 10:
//		return "Resource\\sprites\\Items\\ROSARY.png";
//		break;
//	case 11:
//		return "Resource\\sprites\\Items\\SMALL_HEART.png";
//		break;
//	case 12:
//		return "Resource\\sprites\\Items\\STOP_WATCH.png";
//		break;
//	case 13:
//		return "Resource\\sprites\\Items\\TRIPLE_SHOT.png";
//		break;
//	default:
//		break;
//	}
//}
Item::Item(char* link, int X, int Y)
{
	_texture = new Texture(link, 1, 1, 1);
	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	remainingTime = 500;
	currentPos = x;
	if (link == HEART_PATH)
	{
		tag = HEART_TAG;
	}
	else if (link == WHIP_PATH)
	{
		tag = WHIP_TAG;
	}
	else if (link == KNIFE_PATH)
	{
		tag = KNIFE_TAG;
	}
	else if (link == AXE_PATH)
	{
		tag = AXE_TAG;
	}
	else if (link == HOLYWATER_PATH)
	{
		tag = HOLYWATER_TAG;
	}
	else if (link == ROSARY_PATH)
	{
		tag = ROSARY_TAG;
	}
	else if (link == STOPWATCH_PATH)
	{
		tag = STOPWATCH_TAG;
	}
	else if (link == REDBAG_PATH)
	{
		tag = REDBAG_TAG;
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
	if (!isDead) {
		left = x;
		top = y;
		right = x + _texture->FrameWidth;
		bottom = y + _texture->FrameHeight;
	}

}

void Item::Update(DWORD dt, float simonx, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isDead)
	{
		if (remainingTime < 0)
		{
			isDead = true;
		}
		else if (tag == HEART_TAG)
		{

			CGameObject::Update(dt);

			if (x > currentPos + 35)
			{
				CheckRight = true;
				CheckLeft = false;
			}
			if (x < currentPos - 35)
			{
				CheckRight = false;
				CheckLeft = true;
			}
			if (CheckRight)
			{
				vx = -0.05f;

			}
			if (CheckLeft)
			{
				vx = 0.05f;

			}
			if (!CheckLeft && !CheckRight)
			{
				vx = 0.05f;
			}
			vy = 0.05f;


		}
		else
		{
			CGameObject::Update(dt);
			vy = 0.1f;

			remainingTime--;
		}



		vector<LPGAMEOBJECT> coObjects_Brick;
		coObjects_Brick.clear();
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->GetTag() == BRICK_TAG)
				coObjects_Brick.push_back(coObjects->at(i));
		}
		CollisionWithBrick(&coObjects_Brick);

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
void Item::CollisionWithBrick(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		//x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		//if (nx != 0)
		//{
		//	//vx = 0;
		//	vy = 0;
		//	//isGrounded = true;
		//}

		//if (ny != 0)
		//{
		//	isGrounded = true;
		//	vx = 0;
		//	vy = 0;
		//}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}