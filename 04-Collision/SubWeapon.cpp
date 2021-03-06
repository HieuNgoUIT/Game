﻿#include "SubWeapon.h"

SubWeapon::SubWeapon()
{
	
}


SubWeapon::~SubWeapon()
{
}


void SubWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;

}

void SubWeapon::Update(DWORD dt, float left, float right, vector<LPGAMEOBJECT>* coObjects)
{

}

void SubWeapon::CollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (isColliding(this, coObjects->at(i)))
		{

			if (dynamic_cast<Boss *>(coObjects->at(i)))
			{
				Boss *mm = dynamic_cast<Boss *>(coObjects->at(i));
				coObjects->at(i)->health -= 10;
				mm->StartUntouchable();
			}
			else
			{
				coObjects->at(i)->health -= 10;
			}
			//this->isFinish = true;//da ban xong

		}

	}

}

void SubWeapon::Create(float simonX, float simonY, int simondirection)
{

}

void SubWeapon::Render(Camera * camera)
{

	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == -1)
		_sprite->Draw(pos.x, pos.y);
	else
		_sprite->DrawFlipX(pos.x, pos.y);
	RenderBoundingBox(camera);


}
