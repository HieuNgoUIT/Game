#include "Whip.h"

Whip::Whip(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Weapons\\whip1.png", 4, 3, 12);
	_sprite = new Sprite(_texture, 100);
	x = X;
	y = Y;
	tag = 2;
	typeOfWhip = 0;//whip lv dau
	//health = 1;
	//isFinish = 1;
}

Whip::Whip()
{
	/*_texture = new Texture("Resource\\sprites\\Weapons\\whip1.png", 4, 3, 12);
	_sprite = new Sprite(_texture, 100);*/

}

Whip::~Whip()
{
}

void Whip::RenderBoundingBox(Camera * camera)
{
	CGameObject::RenderBoundingBox(camera);
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (typeOfWhip == 0)
	{

		if (direction == -1)
		{
			left = x;
			top = y;
			right = x + 60;
			bottom = y + _texture->FrameHeight;
		}
		else
		{
			left = x;
			top = y;
			right = x + _texture->FrameWidth - 55;
			bottom = y + _texture->FrameHeight - 20;
		}
	}
	else if (typeOfWhip == 1)
	{
		if (direction == -1)
		{
			left = x - 100;
			top = y;
			right = x;
			bottom = y + _texture->FrameHeight;
		}
		else
		{
			left = x;
			top = y;
			right = x + _texture->FrameWidth;
			bottom = y + _texture->FrameHeight - 20;
		}
	}
	/*else
	{
		left = x;
		top = y;
		right = x + _texture->FrameWidth;
		bottom = y + _texture->FrameHeight;
	}*/


}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	int index = _sprite->GetIndex();
	

	if (typeOfWhip == 0)
	{
		if (index == 3)
		{
			if (index < 0 || index >= 2)//update main whip
				_sprite->SelectIndex(0);
			isFinish = true;
		}
	}

	
	if (typeOfWhip == 1)
	{
		if (index < 4 || index >= 7)
		{
			_sprite->SelectIndex(4);
		}
		if (index == 7)
		{
			isFinish = true;
		}
	}	
	_sprite->Update(dt);
	//CGameObject::Update(dt);
	vector<LPGAMEOBJECT> coObjects_LargeCandle;
	coObjects_LargeCandle.clear();
	for (int i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == 41)
			coObjects_LargeCandle.push_back(coObjects->at(i));
	CollisionWithLargeCandle(&coObjects_LargeCandle);
}
void Whip::CollisionWithLargeCandle(vector<LPGAMEOBJECT>* coObjects)
{
	/*vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();*/

	//CalcPotentialCollisions(coObjects, coEvents); // Lấy danh sách các va chạm
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (isColliding(this, coObjects->at(i)))
		{
			coObjects->at(i)->isDead = true;

		}

	}
	// No collision occured, proceed normally
/*if (coEvents.size() == 0)
{

}
else
{
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	}*/
	// Collision logic with Goombas
//for (UINT i = 0; i < coEventsResult.size(); i++)
//{
//	LPCOLLISIONEVENT e = coEventsResult[i];
//	if (dynamic_cast<LargeCandle *>(e->obj))
//	{
//		LargeCandle *largecandle = dynamic_cast<LargeCandle *>(e->obj);
//		// jump on top >> kill Goomba and deflect a bit 
//		if (e->nx != 0)
//		{
//			largecandle->isDead = true;
//		}
//	}
//}


// clean up collision events
/*for (UINT i = 0; i < coEvents.size(); i++)
	delete coEvents[i];*/
}
void Whip::Create(float simonX, float simonY, int simondirection)
{
	this->x = simonX;
	this->y = simonY;
	this->direction = simondirection;
	isFinish = false;
	this->_sprite->SelectIndex(0);
}
void Whip::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == -1)
		_sprite->Draw(pos.x - 30, pos.y + 5);
	else
		_sprite->DrawFlipX(pos.x - 33, pos.y);
	RenderBoundingBox(camera);
}
