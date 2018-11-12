#include "Whip.h"

Whip::Whip(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Weapons\\whip1.png", 4, 3, 12);
	_sprite = new Sprite(_texture, 100);
	x = X;
	y = Y;
	tag = 2;
	health = 1;
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
	if (_sprite->GetIndex() == 0 || _sprite->GetIndex() == 1 || _sprite->GetIndex() == 2)
	{
		left = x;
		top = y;
		right = x + _texture->FrameWidth-55;
		bottom = y + _texture->FrameHeight-20;
	}
	else
	{
		left = x;
		top = y;
		right = x + _texture->FrameWidth;
		bottom = y + _texture->FrameHeight;
	}

}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	/*if (stopFrame != 3)
	{
		stopFrame = _sprite->GetIndex();
	}
	else
	{
		stopFrame = 0;
	}*/
	
		//_sprite->SelectIndex(0);

		_sprite->Update(dt);
		if (_sprite->GetIndex() == 3)
		{
			isFinish = true;
		}

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
			coObjects->at(i)->isDead=true;
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
void Whip::Create(float simonX, float simonY, int simonTrend)
{
	this->x = simonX;
	this->y = simonY;
	this->trend = simonTrend;
	isFinish =false;
	this->_sprite->SelectIndex(0);
}
void Whip::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (trend == -1)
		_sprite->Draw(pos.x-70, pos.y+5);
	else
		_sprite->DrawFlipX(pos.x-33, pos.y);
	RenderBoundingBox(camera);
}
