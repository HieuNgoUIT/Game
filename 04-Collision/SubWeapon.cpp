﻿#include "SubWeapon.h"

SubWeapon::SubWeapon(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Sub_weapons\\KNIFE.png", 1, 1, 1);
	_sprite = new Sprite(_texture, 100);
	x = X;
	y = Y;
	vx = 1.0f;
	tag = 3;
}

SubWeapon::SubWeapon()
{
}

SubWeapon::~SubWeapon()
{
}

void SubWeapon::RenderBoundingBox(Camera * camera)
{
	CGameObject::RenderBoundingBox(camera);
}

void SubWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

void SubWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += vx;
	_sprite->Update(dt);
	//CGameObject::Update(dt);
	vector<LPGAMEOBJECT> coObjects_LargeCandle;
	coObjects_LargeCandle.clear();
	for (int i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetTag() == 41)
			coObjects_LargeCandle.push_back(coObjects->at(i));
	CollisionWithLargeCandle(&coObjects_LargeCandle);
}

void SubWeapon::CollisionWithLargeCandle(vector<LPGAMEOBJECT>* coObjects)
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

void SubWeapon::Create(float simonX, float simonY, int simondirection)
{
}

void SubWeapon::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == -1)
		_sprite->Draw(pos.x , pos.y );
	else
		_sprite->DrawFlipX(pos.x , pos.y);
	RenderBoundingBox(camera);
}