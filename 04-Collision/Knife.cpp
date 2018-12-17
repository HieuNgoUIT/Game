#include "Knife.h"

Knife::~Knife()
{
}
Knife::Knife(int X,int Y)
{
	_texture = new Texture("Resource\\sprites\\Sub_weapons\\KNIFE_ACTION.png", 1, 1, 1);
	_sprite = new Sprite(_texture, 100);
	x = X;
	y = Y;
	vx = 10.0f;
	tag = 3;
	//isDead = false;
}
void Knife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	remainingTime--;
	if (remainingTime < 0)
	{
		this->isFinish = true;
	}
	CGameObject::Update(dt);
	if (direction == -1)
	{
		x -= vx;
	}
	else
	{
		x += vx;
	}
	vector<LPGAMEOBJECT> coObjects_LargeCandle;
	coObjects_LargeCandle.clear();
	for (int i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetTag() == 10)
			coObjects_LargeCandle.push_back(coObjects->at(i));
	CollisionWithEnemy(&coObjects_LargeCandle);
}
void Knife::Create(float simonX, float simonY, int simondirection)
{

	this->x = simonX;
	this->y = simonY;
	this->direction = simondirection;
	this->remainingTime = 70;//set thoi gian ton tai vu khi
	this->isFinish = false;

}