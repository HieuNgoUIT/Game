#include "Zombie.h"
#pragma once

Zombie::Zombie(int X, int Y,int direction)
{
	_texture = new Texture("Resource\\sprites\\Enemies\\ZOMBIE.png", 2, 1, 2);
	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	startXpos = X;
	startYpos = Y;
	tag = 500;//enemy from 500
	//direction = -1;
	this->direction = direction;
	vx = 1;
	vy = 10;
	health = 10;
}

Zombie::~Zombie()
{
}

void Zombie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (health>0)
	{
		left = x;
		top = y;
		right = x + _texture->FrameWidth;
		bottom = y + _texture->FrameHeight;
	}
}

void Zombie::Update(DWORD dt,  float simonx, vector<LPGAMEOBJECT>* coObjects)
{
	if (health<=0)
	{
		CGameObject::UpdateEffect(dt);
		
		reviveTime--;
		if (reviveTime < 0)
		{
			RePosition();
			this->isDead = false;
			
			
		}
	}
	else
	{
		if (simonx > startXpos-640 && simonx < startXpos+320)
		{

			
			if (x<startXpos-640 || x>startXpos + 640)
			{
				direction = -direction;
			}
			
			vx = 0.05f*direction;
			vy = 0.5f;
			
			
			CGameObject::Update(dt);
			//y += vy;
			_sprite->Update(dt);

			vector<LPGAMEOBJECT> coObjects_Brick;
			coObjects_Brick.clear();
			for (int i = 0; i < coObjects->size(); i++)
			{
				if (coObjects->at(i)->GetTag() == 41)
					coObjects_Brick.push_back(coObjects->at(i));
			}
			CollisionWithBrick(&coObjects_Brick);
		}
		
	}
	
}

void Zombie::Render(Camera * camera)
{
	if (health>0)
	{

		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (direction == -1)
			_sprite->Draw(pos.x, pos.y);
		else
			_sprite->DrawFlipX(pos.x, pos.y);
		RenderBoundingBox(camera);
	}
	else
	{
		CGameObject::RenderEffect(camera);
	}
		
	
}

void Zombie::CollisionWithBrick(vector<LPGAMEOBJECT>* coObjects)
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
		
		x += min_tx * dx + nx * 0.4f;		
		y += min_ty * dy + ny * 0.4f; 

		if (nx != 0)
			vx = 0; 

		if (ny != 0)
		{
			vy = 0;
		
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Zombie::RePosition()
{
	this->x = startXpos;
	this->reviveTime = 200;
	this->hiteffect->isDoneRender = false;
	this->deadffect->isDoneRender = false;
	health = 10;
}
