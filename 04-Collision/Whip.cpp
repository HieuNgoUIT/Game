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
	vector<LPGAMEOBJECT> coObjects_Candle;
	coObjects_Candle.clear();
	vector<LPGAMEOBJECT> coObjects_Zombie;
	coObjects_Zombie.clear();
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->GetTag() == 10)
			coObjects_LargeCandle.push_back(coObjects->at(i));
		if (coObjects->at(i)->GetTag() == 11)
			coObjects_Candle.push_back(coObjects->at(i));
		if (coObjects->at(i)->GetTag() == 500)
			coObjects_Zombie.push_back(coObjects->at(i));
	}
	CollisionWithZombie(&coObjects_Zombie);
	CollisionWithLargeCandle(&coObjects_LargeCandle);
	CollisionWithCandle(&coObjects_Candle);
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
void Whip::CollisionWithCandle(vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (isColliding(this, coObjects->at(i)))
		{
			coObjects->at(i)->isDead = true;
		}

	}
}
void Whip::CollisionWithZombie(vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (isColliding(this, coObjects->at(i)))
		{
			coObjects->at(i)->isDead = true;

		}

	}
	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;

	//coEvents.clear();

	//CalcPotentialCollisions(coObjects, coEvents); // Lấy danh sách các va chạm

	//											  //if (isOnStair)
	//											  //{
	//											  //	for (int i = 0; i < coObjects->size(); i++) //aabb item
	//											  //	{
	//											  //		if (isColliding(this, coObjects->at(i)))
	//											  //		{
	//											  //			isOnStair = false;
	//											  //			this->y = y - 25;



	//											  //		}
	//											  //	}
	//											  //}

	//											  // No collision occured, proceed normally
	//if (coEvents.size() == 0)
	//{
	//	/*x += dx;
	//	y += dy;*/
	//}
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny;

	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	//	// nếu ko va chạm thì min_tx,min_ty = 1.0, còn nếu có thì nó trả về thời gian va chạm. 
	//	//Còn nx,ny là hướng va chạm,  = 0 nếu ko va chạm;

	//	// block 
	//	//	x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	//	//y += min_ty * dy + ny * 0.4f; // ny = -1 thì hướng từ trên xuống....

	//	if (nx != 0)
	//		vx = 0; // nếu mà nx, ny <>0  thì nó va chạm rồi. mà chạm rồi thì dừng vận tốc cho nó đừng chạy nữa

	//	if (ny != 0)
	//	{
	//		vy = 0;
	//		
	//	}

	//	// Collision logic with Goombas
	//	for (UINT i = 0; i < coEventsResult.size(); i++)
	//	{
	//		LPCOLLISIONEVENT e = coEventsResult[i];
	//		if (dynamic_cast<Zombie *>(e->obj))
	//		{
	//			Zombie *zombie = dynamic_cast<Zombie *>(e->obj);
	//			// jump on top >> kill Goomba and deflect a bit 
	//			if (e->ny < 0)
	//			{
	//				zombie->isDead = true;
	//			}
	//			else if (e->nx != 0)
	//			{
	//				zombie->isDead = true;
	//			}
	//		}
	//	}
	//}


	//// clean up collision events
	//for (UINT i = 0; i < coEvents.size(); i++)
	//	delete coEvents[i];
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
