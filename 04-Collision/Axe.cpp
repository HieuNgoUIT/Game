#include "Axe.h"

Axe::~Axe()
{
}
Axe::Axe(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Sub_weapons\\AXE_ACTION.png", 4, 1, 4);
	_sprite = new Sprite(_texture, 100);
	x = X;
	y = Y;
	tag = 3;
	currentPos = y;
	//isDead = false;
}
void Axe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	

	remainingTime--;
	if (remainingTime < 0)
	{
		this->isFinish = true;
		this->CheckTop = false;
	}
	if (!isFinish)
	{
		if (!CheckTop)
		{
			vx = 0.3f*direction;
			vy = -0.5f;
		}
		
		CGameObject::Update(dt);
		x += dx;
		y += dy;
		if (y < currentPos - 150)
		{
			CheckTop = true;
		}
		if (CheckTop)
		{
			vx= 0.4f*direction;
			vy = 0.5f;
		}
		_sprite->Update(dt);
	}
	



	vector<LPGAMEOBJECT> coObjects_LargeCandle;
	coObjects_LargeCandle.clear();
	for (int i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetTag() == ENEMY_TAG)
			coObjects_LargeCandle.push_back(coObjects->at(i));
	CollisionWithEnemy(&coObjects_LargeCandle);
}
void Axe::Create(float simonX, float simonY, int simondirection)
{
	this->x = simonX;
	this->y = simonY;
	this->direction = simondirection;
	this->remainingTime = 70;//set thoi gian ton tai vu khi
	this->isFinish = false;
	this->CheckTop = false;

}
